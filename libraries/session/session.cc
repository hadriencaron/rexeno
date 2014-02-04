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
  : _trialsOrder(o.getOrder()),
    _R(0),
    _G(0),
    _B(0)
{
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
  recorder = new Recorder("/tmp/", s.traceLevel);
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
  recorder->Save(s.traceLevel, "general.txt");

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
 * Reshape the window's size
 */
void
reshape(int width, int height){
	if (height==0){
		height=1;
	}
	if (width <= height){
		glOrtho (-50, 50, -50*height/width, 50*height/width, -1, 1);
	}
	else{
		glOrtho (-50*width/height, 50*width/height, -50, 50, -1, 1);
	}
	glViewport(0,0,width, height); //Taille de la zone de sortie
	glMatrixMode(GL_PROJECTION); // Charge la matrice de données GL_PROJECTION = Forme
	glLoadIdentity(); // Reset la matrice
	gluPerspective(90, float(width/height), 0.1f, 150.0f); // Angle de la perspective, largeur de celle-ci et zone de clipping
	glMatrixMode(GL_MODELVIEW); // GL_MODELVIEW = Camera

}

GLvoid
InitGL(int width, int height){

	float Sun =  0.5f;
	float rgb[3] = {0.0f, 0.51f, 0.73f};

	GLfloat lightPosition[4] = {0.0f,1.0f,0.0f,0.0f};
	GLfloat lightAmbient[4] = {Sun,Sun,Sun,2.0f};
	GLfloat lightDiffuse[4] = {1.0f,1.0f,1.0f,1.0f};

	glEnable(GL_TEXTURE_2D);
 	glClearColor(rgb[0],rgb[1],rgb[2],1.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );

	glEnable(GL_DEPTH_TEST); // est de profondeur
	glEnable(GL_LIGHTING); // Active l'éclairage
	glEnable(GL_LIGHT0); // Allume la lumière numero 1;

	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glEnable(GLUT_DEPTH || GLUT_DOUBLE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


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
  /*  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
  	glutInitWindowSize(2048, 768);*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(3840,1080);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,
			               (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
	//glutInitWindowPosition(0, 0);
	glutCreateWindow ((char*)"Time in Dynamic Perspective");;

	//glutGameModeString("1920x1080:32@60");
	//glutEnterGameMode();
	glutKeyboardFunc(processNormalKeys);
	 // glutFullScreen();
	 // glutSetCursor(GLUT_CURSOR_NONE);
	glutReshapeFunc(&reshape);
	glutDisplayFunc (displayRexeno);

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	InitGL(3840,1080);

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
 // PDEBUG("Session::displayFrame ", __debug_FrameNumber << "/" << _trialsOrder.size() << " trials in this session");
#endif


  if (_currentTrial != _trialsOrder.end())
  {
  //  PDEBUG("Session::displayFrame", " trial frame ");
    Trial* t = _trialsDefinitions[*_currentTrial];
    if (t->atStart() && beforeTrial)
    {
   //   std::cout << "Name => " << t->variables << endl;
      beforeTrial(t->name(), t->variables);
      t->adjustNbFrames();	printf("3\n");
    };
    int b = t->displayFrame(_driver);

    if (b != RUNNING)
    {

    // PDEBUG("Session::displayFrame", " end of trial : " << t->name() << " (trial number " << *_currentTrial << " )");
      ms displayTime = _driver->GetTime();
      recorder->Save("EndTrial " + lexical_cast<string>(displayTime), "events.txt");
      if (afterTrial)

        afterTrial(t->name(), t->variables, b);

      _currentTrial++;
      t->Reset(_driver);
#ifdef DEBUG
      ++__debug_FrameNumber;
#endif
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
