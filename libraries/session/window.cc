#include "window.hh"

Window::Window(const ShapeInfo&,
               variableManager&,
               Trial*)
{
  assert(si.attributes.size() == 11);
  assert(!father);
  _name = "Rectangle";
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(si.attributes[5]));
  vm.addVariable(_G = new Variable(si.attributes[6]));
  vm.addVariable(_B = new Variable(si.attributes[7]));
  vm.addVariable(_width = new Variable(si.attributes[8]));
  vm.addVariable(_height = new Variable(si.attributes[9]));

  _ttl = lexical_cast<int>(si.attributes[10]);

  _father = father;
}

void
Window::display()
{

}

void
Window::displayMonitor()
{
  double leftX = _xGL() - _demiHorizontal();
  double rightX = _xGL() + _demiHorizontal();
  double topY = _yGL() + _demiVertical();
  double bottomY = _yGL() + _demiVertical();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);    
  glVertex2d(leftX, topY);
  glVertex2d(leftX - _thickness, topY);
  glVertex2d(leftX - _thickness, bottomY);
  glVertex2d(leftX, bottomY);
  glEnd();
}

bool
Window::isIn(double x,
             double y)
{
  double leftX = *_x - (*_width / 2);
  double rightX = *_x + (*_width / 2);
  double bottomY = *_y - (*_height / 2);
  double topY = *_y + (*_height / 2);
  bool res = true;

  res &= (x > leftX) && (x < rightX);
  res &= (y > bottomY) && (y < topY);
  return (res);
}

