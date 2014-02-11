#include "session.hh"
#include "parser.hh"
#include "trial.hh"
#include "setup.hh"

#include "driver.hh"
#include "order_parser.hh"
#include <GL/glut.h>
#include <boost/lexical_cast.hpp>
#include <sys/mman.h>
#include "fileCalibration.hh"

using namespace configuration;

Session* Session::_instance = NULL;

/** 
 * Constructor :
 * Inits all the fields automatically
 * only the _trials field will depend on
 * what information is in the SessionInfo parameter
 * 
 * @param s 
 */
Session::Session(configuration::SessionInfo& s,
                 Order& o)
  : 
    _R(0),
    _G(0),
    _B(0),
    _name(s.name),
    _enableReplay(s.enable_replay)
{
  mlockall(MCL_CURRENT | MCL_FUTURE); // No page faults, memory is immediately allocated by the kernel.
  // Set channels corresponding to x and y coordinates
  _x_channel = boost::lexical_cast<int>(s.x_channel);
  _y_channel = boost::lexical_cast<int>(s.y_channel);
  // Set corrdinates type (pcents, cm or degrees)
  _coordinates_type = s.coordinates_type;
  // Copy the vector containing the trial orders. TODO : isn't a reference copy possible ?
  _trialsOrder = o.getOrder();
  Trial* t = NULL;
  vector<TrialInfo>::iterator it;

  for (it = s.trials.begin(); it != s.trials.end(); ++it)
  {
    t = new Trial(*it, this);
    _trialsDefinitions.push_back(t);
  }
  _currentTrial = _trialsOrder.begin();
  beforeTrial = NULL;
  afterTrial = NULL;
  _inputData.resize(8);
  recorder = new Recorder("/tmp/", 10);
  recorder->AddFile("results.txt");
  recorder->AddFile("events.txt");
  recorder->AddFile("X.txt");
  recorder->AddFile("id_trials.txt");
  recorder->AddFile("square_targets.txt");
  recorder->AddFile("logger.txt");
  recorder->AddFile("general.txt");

  _offsetVsync = -1;
  _initialized = false;
  _nbFrame4init = 120;
  _nbInitFrames = 0;
#ifdef DEBUG
  __debug_FrameNumber = 0;
#endif

  recorder->Save(s.name, "general.txt");

  _driverType = s.driver;
  Calibration* cal = CalibrationCreator(s.calibration_type);
  _driver = DriverCreator(s.driver, cal);
  
}

Calibration*
Session::CalibrationCreator(std::string calibrationName)
{
  if (calibrationName == "keyboard")
  {
    return (new KeyboardCalibration());
  }
  else if (calibrationName.find("matrix:") == 0)
  {
    std::string filename = calibrationName.substr(7); // from end of "file:" till the end
    PDEBUG("Session::DriverCreator ", "FileDriver requested : " << filename);
    return (new FileCalibration(filename));
  }
  else
  {
    cerr << "Wrong calibration type, should be one of 'keyboard', 'no', or 'matrix:<filename>'" << endl;
    cerr << "current value is " << calibrationName << endl;
    throw ;
  }
  return NULL;
}

Driver*
Session::DriverCreator(std::string driverName,
                       Calibration* cal)
{
  if (driverName == "xeno")
  {
#ifdef XENO
    PDEBUG("Session::DriverCreator ", "XenoDriver requested")
    return(new XenoDriver(this, cal));
#else
    //return(new DummyDriver(this, cal));
    cerr << "XenoDriver requested but installed with -DNOXENO=YES" << endl;
    throw ;
#endif
  }
  else if (driverName == "dummy")
  {
    PDEBUG("Session::DriverCreator ", "DummyDriver requested")
    return(new DummyDriver(this, cal));
  }
  else if ((driverName.find("file:")) == 0)
  {
    std::string filename = driverName.substr(5); // from end of "file:" till the end
    PDEBUG("Session::DriverCreator ", "FileDriver requested : " << filename);
    return(new FileDriver(this, cal, filename));
  }
  else
  {
    cerr << "Wrong driver type, should be one of 'dummy', 'xeno', or 'file:<filename>'" << endl;
    throw ;
  }
  return NULL;
}


/** 
 * Destructor : cleans everything up
 * TODO : this destructor is stupid and
 * probably not even called (program exited before)
 */
Session::~Session()
{
  PDEBUG("Session::~Session ", "start");
  vector<Trial*>::iterator it;
  for (it = _trialsDefinitions.begin(); it != _trialsDefinitions.end(); ++it)
  {
    delete (*it);
  }
  delete recorder;
  recorder = NULL;
  delete _instance;
  _instance = NULL;
  delete setup;
  setup = NULL;
}

/** 
 * function set as the main GLUT callback
 * 
 */
void
displayRexeno()
{
  PDEBUG("displayRexeno", "start");
  Session* s = Session::getInstance();
  s->displayHeader();
}

/** 
 * If session is initialized : show trial
 * else : show dummy GL_QUAD to calculate displaying delay
 * 
 */
void
Session::displayHeader()
{
  PDEBUG("Session::displayHeader", "start");
  if (!initialized())
  {
    glBegin(GL_QUADS);
    glColor3ub(255, 155, 255);    
    glVertex2d(-0.1, -0.1);
    glVertex2d(-0.1, 0.1);
    glVertex2d(0.1, -0.1);
    glVertex2d(0.1, 0.1);
    glEnd();


    glutSwapBuffers();
    glutPostRedisplay();
    glClear(GL_COLOR_BUFFER_BIT);
    if (nbInitFrames() < nbFrame4init())
    {
      //getTime() % (int) setup->refreshRate();
      ++_nbInitFrames;
    }
    else
    {
      _initialized = true;
      _driver->InitTime();
    }
  }
  else
  {
    PDEBUG("Session::displayHeader ", "request a session:displayFrame");
    displayFrame();
  }
}

/** 
 * Opengl's keyboard/mouse processing callback
 * 
 * @param key : id of a keyboard key that was pressed
 * @param x : horizontal position of the mouse
 * @param y : vertical position of the mouse
 */
void processNormalKeys(unsigned char key, int x, int y) 
{
  Setup::keys[key] = true;
  if (key == 27) 
  {
    PDEBUG("processNormalKeys ", "escape pressed");
    exit(0);
  }
}

/** 
 * Inits and launch the GLUT loop
 * 
 * @param argc 
 * @param argv 
 */
void
Session::run(int argc,
             char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(2048, 768);
  glutCreateWindow ((char*)"rexeno");
  glutGameModeString("2048x768:32@60");
  glutEnterGameMode();
  glutKeyboardFunc(processNormalKeys);
  glutFullScreen();
  glutSetCursor(GLUT_CURSOR_NONE);
  glutDisplayFunc (displayRexeno);
  glEnable(GLUT_DEPTH || GLUT_DOUBLE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(_R, _G, _B, 1.0f);
  glutMainLoop();
}

/** 
 * displays a single frame of the Session (must return quickly in order for the GLUT loop to
 * continue smoothly)
 * 
 */
void
Session::displayFrame()
{
#ifdef DEBUG
  PDEBUG("Session::displayFrame ", __debug_FrameNumber << "/" << _trialsOrder.size() << " trials in this session");
#endif


  if (_currentTrial != _trialsOrder.end())
  {
    PDEBUG("Session::displayFrame", " trial frame ");
    Trial* t = _trialsDefinitions[*_currentTrial];

    if (t->atStart() && beforeTrial)
    {
      beforeTrial(t->name(), t->variables);
    }

    int b = t->displayFrame(_driver);

    if (t->status(CORRECT) || (t->status(WRONG_NEXT)) || (t->status(WRONG_REDO)))
    {
      PDEBUG("Session::displayFrame", " end of trial is : " << t->name() << " (trial number " << *_currentTrial << " )");
      ms displayTime = _driver->GetTime();
      recorder->Save(lexical_cast<string>(displayTime) + " EndTrial", "events.txt");
      if (afterTrial)
        afterTrial(t->name(), t->variables, b);

      if (b != WRONG_REDO)
      {
        PDEBUG("Session::displayFrame ", "request next trial");
        if (t->status(CORRECT))
          recorder->Save("1", "results.txt");
        if (t->status(WRONG_NEXT))
          recorder->Save("0", "results.txt");
        _currentTrial++;
#ifdef DEBUG
        ++__debug_FrameNumber;
#endif
      }
      t->Reset();
      PDEBUG("Session::displayFrame ", "Reset finished");
    }
  }
  else
  {
    PDEBUG("Session::displayTime", " regular exit")
    exit (0);
  }

}

/** 
 * Standard SINGLETON member
 * 
 * 
 * @return 
 */
Session*
Session::getInstance()
{
  return _instance; 
}

/** 
 * Standard SINGLETON member
 * 
 * @param s 
 * 
 * @return 
 */
Session*
Session::getInstance(configuration::SessionInfo& s,
                     Order& o)
{
  _instance = new Session(s, o);

  return (_instance);
}

ms
Session::getTime()
{
  assert (_driver);
  return _driver->GetTime();
}

bool
Session::initialized()
{
  return (_initialized);
}
