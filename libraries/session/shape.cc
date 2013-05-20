#include "shape.hh"
#include <GL/glut.h>
#include <boost/lexical_cast.hpp>
#include "session.hh"

using boost::lexical_cast;

void
Shape::display()
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

void
Shape::displayMonitor()
{
  display();
}

bool
Shape::displayable(int frameId)
{
  bool res = true;

  res &= (frameId >= frameStart()) || (frameStart() == -1);
  res &= (frameId <= frameEnd()) || (frameEnd() == -1);
  return res;
}

bool
Shape::monitorDisplayable()
{
  return ((*_x + *_width / 2) < 1);
}

double
Shape::_demiVertical()
{
  Session* s = Session::getInstance();
  double xRatio = s->setup->xRatio();
  double demi_vertical = xRatio * *_width / 2;
  return (demi_vertical);
}

double
Shape::_demiHorizontal()
{
  Session* s = Session::getInstance();
  double yRatio = s->setup->yRatio();
  double demi_horizontal = yRatio * *_height / 2 / 2;
  return (demi_horizontal);
}

double
Shape::_xGL()
{
  Session* s = Session::getInstance();
  double xRatio = s->setup->xRatio();
  double xGL = *_x * xRatio / 2;
  return xGL;
}

double
Shape::_yGL()
{
  Session* s = Session::getInstance();
  double yRatio = s->setup->yRatio();
  double yGL = *_y * yRatio;
  return yGL;
}

void
Shape::react2input(Status& s,
                   datas& ds,
                   int frameId,
                   ms displayTime)
{
  Session* session = Session::getInstance();
  cout << frameId << " " << frameStart() << " " << frameEnd() << endl;
  if ((frameId == frameStart()) && (!_logged))
  {
    _logged = true;
    session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " start", "events.txt");
  }
  if ((frameId == frameEnd()) && (!_loggedEnd))
  {
    session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " end", "events.txt");
    _loggedEnd = true;
  }

  if (frameId > frameEnd())
    s[RUNNING] |= false;
  else
    s[RUNNING] = true;

  
  session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " display", "logger.txt");
}

Shape::Shape()
{
  _logged = false;
  _loggedEnd = false;
  _subjectVisible = true;
}

