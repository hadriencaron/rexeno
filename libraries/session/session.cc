#include "session.hh"
#include "trial.hh"
#include "setup.hh"

Session* Session::_instance = NULL;

Session::Session(SessionInfo &s)
  : _R(0),
    _G(0),
    _B(0)
{
  Trial* t = NULL;
  vector<TrialInfo>::iterator it;

  for (it = s.trials.begin(); it != s.trials.end(); ++it)
    {
      t = new Trial(*it);
      _trials.push_back(t);
    }
  _currentTrial = _trials.begin();

  beforeTrial = NULL;
  afterTrial = NULL;
  _inputData.resize(8);
  _driver = NULL;
  recorder = new Recorder("/tmp/");
  recorder->AddFile("results.txt");
  recorder->AddFile("events.txt");
  recorder->AddFile("X.txt");
  recorder->AddFile("id_trials.txt");
  recorder->AddFile("square_targets.txt");

  _offsetVsync = -1;
  _initialized = false;
  _nbFrame4init = 120;
  _nbInitFrames = 0;
}

Session::~Session()
{
  vector<Trial*>::iterator it;
  for (it = _trials.begin(); it != _trials.end(); ++it)
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

void
displayRexeno()
{
  Session* s = Session::getInstance();
  s->displayHeader();
}

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


void processNormalKeys(unsigned char key, int x, int y) 
{
  Setup::keys[key] = true;
  if (key == 27) 
    {
      exit(0);
    }
}

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

void
Session::displayFrame()
{
  if (_currentTrial != _trials.end())
  {
    Trial* t = *_currentTrial;

    if (t->atStart() && beforeTrial)
    {
      beforeTrial(t->name(), t->variables);
      t->adjustNbFrames();
    }

    int b = (*_currentTrial)->displayFrame(_driver);

    if (b != RUNNING)
    {
      ms displayTime = _driver->getTime();
      recorder->Save("EndTrial " + lexical_cast<string>(displayTime), "events.txt");
      if (afterTrial)
        afterTrial(t->name(), t->variables, b);

      _currentTrial++;
    }
  }
  else
    exit (0);

}

Session*
Session::getInstance()
{
  return _instance; 
}

Session*
Session::getInstance(SessionInfo& s)
{
  _instance = new Session(s);

  return (_instance);
}

void
Session::_fillData()
{

}


ms
Session::getTime()
{
  assert (_driver);
  return _driver->getTime();
}

bool
Session::initialized()
{
  return (_initialized);
}
