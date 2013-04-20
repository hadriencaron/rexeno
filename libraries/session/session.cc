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
}

Session::~Session()
{

}

void
displayRexeno()
{
  Session* s = Session::getInstance();

  s->displayFrame();
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

    int b = (*_currentTrial)->displayFrame(*_driver);

    if (t->finished())
    {
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


