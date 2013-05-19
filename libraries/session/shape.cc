#include "shape.hh"
#include <GL/glut.h>
#include <boost/lexical_cast.hpp>
#include "session.hh"

using boost::lexical_cast;

void
Shape::Display()
{
  double xGL = _Xgl();
  double yGL = _Ygl();
  double demi_horizontal = _DemiHorizontal();
  double demi_vertical = _DemiVertical();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);    
  glVertex2d(xGL-demi_horizontal, yGL-demi_vertical);
  glVertex2d(xGL+demi_horizontal, yGL-demi_vertical);
  glVertex2d(xGL+demi_horizontal, yGL+demi_vertical);
  glVertex2d(xGL-demi_horizontal, yGL+demi_vertical);
  glEnd();
}

void
Shape::DisplayMonitor()
{
  Display();
}

bool
Shape::Displayable(int frameId)
{
  bool res = true;

  res &= (frameId >= FrameStart()) || (FrameStart() == -1);
  res &= (frameId <= FrameEnd()) || (FrameEnd() == -1);
  return res;
}

bool
Shape::MonitorDisplayable()
{
  return ((*_x + *_width / 2) < 1);
}

double
Shape::_DemiVertical()
{
  Session* s = Session::GetInstance();
  double xRatio = s->setup->xRatio();
  double demi_vertical = xRatio * *_width / 2;
  return (demi_vertical);
}

double
Shape::_DemiHorizontal()
{
  Session* s = Session::GetInstance();
  double yRatio = s->setup->yRatio();
  double demi_horizontal = yRatio * *_height / 2 / 2;
  return (demi_horizontal);
}

double
Shape::_Xgl()
{
  Session* s = Session::GetInstance();
  double xRatio = s->setup->xRatio();
  double xGL = *_x * xRatio / 2;
  return xGL;
}

double
Shape::_Ygl()
{
  Session* s = Session::GetInstance();
  double yRatio = s->setup->yRatio();
  double yGL = *_y * yRatio;
  return yGL;
}

void
Shape::React2Input(Status& s,
                   datas& ds,
                   int frameId,
                   ms displayTime)
{
  Session* session = Session::GetInstance();
  if ((frameId == FrameStart()) && (!_logged))
  {
    _logged = true;
    session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " start", "events.txt");
  }
  if ((frameId == FrameEnd()) && (!_loggedEnd))
  {
    session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " end", "events.txt");
    _loggedEnd = true;
  }

  if (frameId > FrameEnd())
    s[RUNNING] |= false;
  else
    s[RUNNING] = true;

}

Shape::Shape()
{
  _logged = false;
  _loggedEnd = false;
}
