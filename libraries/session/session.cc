#include "session.hh"
#include "parser.hh"
#include "trial.hh"
#include "setup.hh"

#include "driver.hh"
#include "order_parser.hh"
#include <GL/glut.h>

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
    _x_channel(s.x_channel),
    _y_channel(s.y_channel),
    _coordinates(s.coordinates)
{
  _trialsOrder = o.getOrder();
  Trial* t = NULL;
  vector<TrialInfo>::iterator it;

  for (it = s.trials.begin(); it != s.trials.end(); ++it)
  {
    t = new Trial(*it);
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

#ifdef XENO
  _driver = new XenoDriver();
#else
  _driver = new DummyDriver();
#endif
}

/** 
 * Destructor : cleans everything up
 * TODO : this destructor is stupid and
 * probably not even called (program exited before)
 */
Session::~Session()
{
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
    }
  }
  else
  {
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
  //glutEnterGameMode();
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
      t->adjustNbFrames();
    }

    int b = t->displayFrame(_driver);

    if ((b != RUNNING) && (b != PAUSE))
    {
      PDEBUG("Session::displayFrame", " end of trial is : " << t->name() << " (trial number " << *_currentTrial << " )");
      ms displayTime = _driver->GetTime();
      recorder->Save("EndTrial " + lexical_cast<string>(displayTime), "events.txt");
      if (afterTrial)
        afterTrial(t->name(), t->variables, b);

      if (b != WRONG_REDO)
      {
        _currentTrial++;
#ifdef DEBUG
        ++__debug_FrameNumber;
#endif
      }
      t->Reset();
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
