#include "shape.hh"
#include <GL/glut.h>

#include "session.hh"

void
Shape::display()
{
  Session* s = Session::getInstance();
  double xRatio = s->setup->xRatio();
  double yRatio = s->setup->yRatio();

  double demi_vertical = *_width / 2;
  double demi_horizontal = *_height / 2;

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);    
  glVertex2d(*_x-demi_horizontal, *_y-demi_vertical);
  glVertex2d(*_x+demi_horizontal, *_y-demi_vertical);
  glVertex2d(*_x+demi_horizontal, *_y+demi_vertical);
  glVertex2d(*_x-demi_horizontal, *_y+demi_vertical);
  glEnd();
}

void
Shape::displayMonitor()
{
  display();
}

bool
Shape::monitorDisplayable()
{
  return ((*_x + *_width / 2) < 1);
}
