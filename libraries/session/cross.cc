#include "cross.hh"
#include <GL/glut.h>
#include "trial.hh"

Cross::Cross(const ShapeInfo& si,
             VariableManager& vm,
             Trial* father)
{
  assert(si.attributes.size() == 9);
  _name = si.attributes[0];
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(si.attributes[5]));
  vm.addVariable(_G = new Variable(si.attributes[6]));
  vm.addVariable(_B = new Variable(si.attributes[7]));
  vm.addVariable(_width = new Variable(si.attributes[8]));
  vm.addVariable(_height = new Variable(si.attributes[8]));

  _father = father;
}

void
Cross::Display()
{


}

void
Cross::DisplayMonitor()
{
  double xGL = _Xgl();
  double yGL = _Ygl();

  double demi_horizontal = _DemiHorizontal();
  double demi_vertical = _DemiVertical();

  double bar_width_horizontal = demi_horizontal / 20;
  double bar_width_vertical = demi_vertical / 20;

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);    
  glVertex2d(xGL-demi_horizontal, yGL-bar_width_vertical);
  glVertex2d(xGL+demi_horizontal, yGL-bar_width_vertical);
  glVertex2d(xGL+demi_horizontal, yGL+bar_width_vertical);
  glVertex2d(xGL-demi_horizontal, yGL+bar_width_vertical);
  glEnd();

  // Barre horizontale

  glBegin(GL_QUADS);
  glVertex2d(xGL-(bar_width_horizontal),yGL-demi_vertical);
  glVertex2d(xGL+(bar_width_horizontal),yGL-demi_vertical);
  glVertex2d(xGL+(bar_width_horizontal),yGL+demi_vertical);
  glVertex2d(xGL-(bar_width_horizontal),yGL+demi_vertical);
  glEnd();
}

void
Cross::React2Input(Status& s,
                   datas& ds,
                   int frameId,
                   ms)
{
  _x->value = ds[0].volt;
  _y->value = - ds[1].volt;
}


