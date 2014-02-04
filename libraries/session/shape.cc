#include "shape.hh"
#include <GL/glut.h>
#include <boost/lexical_cast.hpp>
#include "session.hh"

#include "recorder.hh"
#include "trial.hh"
#include "setup.hh"

using boost::lexical_cast;

/** 
 * Displays the shape on the subject screen
 * 
 */
void
Shape::Display()
{
	double xGL = _xGL();
	double yGL = _yGL();
	double demi_horizontal = _demiHorizontal();
	double demi_vertical = _demiVertical();
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
		glColor3ub(*_R,*_G,*_B);
		glVertex3d(xGL-demi_horizontal, yGL-demi_vertical,0.f);
		glVertex3d(xGL+demi_horizontal, yGL-demi_vertical,0.f);
		glVertex3d(xGL+demi_horizontal, yGL+demi_vertical,0.f);
		glVertex3d(xGL-demi_horizontal, yGL+demi_vertical,0.f);
	glEnd();
	glEnable(GL_LIGHTING);
}

/** 
 * Displays the shape on the monitor screen (experimentator side)
 * 
 */
void
Shape::DisplayMonitor()
{
  Display();
}

/** 
 * Indicate if the shape should appear at the given frame
 * 
 * @param frameId : frame number. 0 for first frame
 * 
 * @return true if the shape should be displayed,
 * else 0
 */
bool
Shape::Displayable(int frameId)
{
  bool res = true;

  res &= (frameId >= frameStart()) || (frameStart() == -1);
  res &= (frameId <= frameEnd()) || (frameEnd() == -1);
 // PDEBUG("Shape::Displayable ", "shape " << name() << " is displayable: " << res << " start " << frameStart() << " end " << frameEnd());
  return res;
}

/** 
 * Checks if the given shape won't appear on the
 * subjects (because of too large coodonates)
 * side if one attempts to display it on the monitor screen
 * 
 * 
 * @return true if is safe to draw,
 * else 0
 */
bool
Shape::MonitorDisplayable()
{
  return ((*_x + *_width / 2) < 1);
}

/** 
 * 
 * FOR OPENGL COORD USAGE :
 * returns the length of the vertical dimension
 * 
 * @return the opengl length adapted to the screen
 */
double
Shape::_demiVertical()
{
  Session* s = Session::getInstance();
  double xRatio = s->setup->xRatio();
  double demi_vertical = xRatio * *_width / 2;
  return (demi_vertical);
}

/** 
 * FOR OPENGL COORD USAGE :
 * returns the length of the vertical dimension
 * 
 * @return the opengl length adapted to the screen
 */
double
Shape::_demiHorizontal()
{
  Session* s = Session::getInstance();
  double yRatio = s->setup->yRatio();
  double demi_horizontal = yRatio * *_height / 2;
  return (demi_horizontal);
}

/** 
 * 
 * FOR OPENGL COORD USAGE
 * 
 * @return the x value adapted to the screen
 */
double
Shape::_xGL()
{
  Session* s = Session::getInstance();
  double xRatio = s->setup->xRatio();
  double xGL = *_x * xRatio / 2;
  return xGL;
}

/** 
 * 
 * FOR OPENGL COORD USAGE
 * 
 * @return the y value adapted to the screen
 */
double
Shape::_yGL()
{
  Session* s = Session::getInstance();
  double yRatio = s->setup->yRatio();
  double yGL = *_y * yRatio;
  return yGL;
}

/** 
 * This function represents the possibility to affect the outcome of
 * a trial according to what is in ds by changing mainly it's paramenters
 * 
 * @param s : the current status of the trial (WRONG, CORRECT, ...)
 * @param ds : (Eye) data extracted from the analog input
 * @param frameId : current frame we are on
 * @param displayTime : what date (in milliseconds) was the frame presented
 */
void
Shape::React2input(Status& s,
                   const datas& ds,
                   int frameId,
                   ms displayTime)
{

  Session* session = Session::getInstance();
  // Saving of shape apparition
  if ((frameId == frameStart()) && (!_logged))
  {
    _logged = true;
	string s;
	ostringstream ostr;
	ostr << _name << " start " << lexical_cast<string>(displayTime) << " Pos [" << *_x << ", " << *_y <<"]";
	s = ostr.str();
	session->recorder->Save(s, "events.txt");
  }
  // Saving of shape disparation
  if ((frameId == frameEnd()) && (!_loggedEnd))
  {
	string s;
	ostringstream ostr;
	ostr << _name << " end " << lexical_cast<string>(displayTime) << " Pos [" << *_x << ", " << *_y <<"]";
	s = ostr.str();
	session->recorder->Save(s, "events.txt");
    _loggedEnd = true;
  }

  session->recorder->Save(_name + "\n" + lexical_cast<string>(this->_x->value) + "\n" + lexical_cast<string>(this->_y->value) + "\n" + lexical_cast<string>(displayTime), "square_targets.txt");

  if (frameId > frameEnd())
    s[RUNNING] |= false;
  else
    s[RUNNING] = true;

  session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " display", "logger.txt");
}

void
Shape::initTexture(int sizeX, int sizeY, char * data){

	glGenTextures(1, &this->_texture[0]);// Donne numero de texture
	glBindTexture(GL_TEXTURE_2D, this->_texture[0]); //Selectionne la texture

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(
		GL_TEXTURE_2D,		//Type de texture
		0,					//Mipmap : aucun
		3,					//Couleurs: 4
		sizeY,					//Largeur: 2
		sizeX,					//Hauteur: 2
		0,					//Largeur des bords: 0
		GL_RGB,			//RGBA format
		GL_UNSIGNED_BYTE,	//Type des couleurs
		data			//Adresse de l'image
	);

	if (_texture[0] != 0){
		_istexured = true;
	}
	else{
		printf("ERROR ! Impossible d'appliquer la texture!");
		exit(0);
	}
}

void
Shape::Reset(){
	printf("ok\n");
//	_logged = false;
//	_loggedEnd = false;
}

/**
 * Abstract Constructor : inits some bool values
 *
 */

string
Shape::getAttrsToString(){
	string s;
	ostringstream ostr;
	ostr << _name << ": Width "<< *_width <<" Height "<<*_height << " Pos ["<< *_x <<", "<< *_y <<"] RGB ["<<*_R<<", "<<*_G<<", "<<*_B<<"]";
	s = ostr.str();
	return s;
}

Shape::Shape()
{
  _id = 0;
  _texture[1] = 0; // not initialized
  _istexured = false;
  _logged = false;
  _loggedEnd = false;
  _subjectVisible = true;
}


