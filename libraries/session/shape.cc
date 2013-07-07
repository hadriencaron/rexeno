#include "shape.hh"
#include <GL/glut.h>
#include <boost/lexical_cast.hpp>
#include "session.hh"

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

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);    
  glVertex2d(xGL-demi_horizontal, yGL-demi_vertical);
  glVertex2d(xGL+demi_horizontal, yGL-demi_vertical);
  glVertex2d(xGL+demi_horizontal, yGL+demi_vertical);
  glVertex2d(xGL-demi_horizontal, yGL+demi_vertical);
  glEnd();
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
Shape::react2input(Status& s,
                   datas& ds,
                   int frameId,
                   ms displayTime)
{
  Session* session = Session::getInstance();
  // cout << frameId << " " << frameStart() << " " << frameEnd() << endl;
  // Saving of shape apparition
  if ((frameId == frameStart()) && (!_logged))
  {
    _logged = true;
    session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " start", "events.txt");
  }
  // Saving of shape disparation
  if ((frameId == frameEnd()) && (!_loggedEnd))
  {
    session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " end", "events.txt");
    _loggedEnd = true;
  }

  session->recorder->Save(_name + "\n" + ((string)*(this->_x)) + "\n" + ((string)*(this->_y)) + "\n" + lexical_cast<string>(displayTime), "square_targets.txt");

  if (frameId > frameEnd())
    s[RUNNING] |= false;
  else
    s[RUNNING] = true;

  

  session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " display", "logger.txt");
}

/** 
 * Abstract Constructor : inits some bool values
 * 
 */
Shape::Shape()
{
  _logged = false;
  _loggedEnd = false;
  _subjectVisible = true;
}

