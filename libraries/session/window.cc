#include "trial.hh"
#include "window.hh"
#include <boost/lexical_cast.hpp>
#include <GL/glut.h>

using namespace boost;
class Trial;

Window::Window(const ShapeInfo& si,
               VariableManager& vm,
               Trial* father)
{
  assert(si.attributes.size() == 11);
  assert(father);
  _name = si.attributes[0];
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
  _thickness = 0.01;

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
  double bottomY = _yGL() - _demiVertical();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex2d(leftX, topY);
  glVertex2d(leftX + _thickness, topY);
  glVertex2d(leftX + _thickness, bottomY);
  glVertex2d(leftX, bottomY);
  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex2d(rightX, topY);
  glVertex2d(rightX - _thickness, topY);
  glVertex2d(rightX - _thickness, bottomY);
  glVertex2d(rightX, bottomY);
  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex2d(leftX, topY);
  glVertex2d(leftX,  topY - _thickness);
  glVertex2d(rightX,  topY - _thickness);
  glVertex2d(rightX, topY);
  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex2d(leftX, bottomY);
  glVertex2d(leftX, _thickness + bottomY);
  glVertex2d(rightX, _thickness + bottomY);
  glVertex2d(rightX, bottomY);
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

CorrectWindow::CorrectWindow(const ShapeInfo& si,
                             VariableManager& vm,
                             Trial* father)
{
  assert(si.attributes.size() == 12);
  assert(father);
  _name = si.attributes[0];
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(si.attributes[5]));
  vm.addVariable(_G = new Variable(si.attributes[6]));
  vm.addVariable(_B = new Variable(si.attributes[7]));
  vm.addVariable(_width = new Variable(si.attributes[8]));
  vm.addVariable(_height = new Variable(si.attributes[9]));
  vm.addVariable(_validationNbFrame = new Variable(si.attributes[10]));

  _ttl = lexical_cast<int>(si.attributes[11]);

  _father = father;
  _startValidationFrame = -1;
  _type = CORRECT;
}

WrongWindow::WrongWindow(const ShapeInfo& si,
                         VariableManager& vm,
                         Trial* father)
{
  assert(si.attributes.size() == 12);
  assert(father);
  _name = si.attributes[0];
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(si.attributes[5]));
  vm.addVariable(_G = new Variable(si.attributes[6]));
  vm.addVariable(_B = new Variable(si.attributes[7]));
  vm.addVariable(_width = new Variable(si.attributes[8]));
  vm.addVariable(_height = new Variable(si.attributes[9]));
  vm.addVariable(_validationNbFrame = new Variable(si.attributes[10]));

  _ttl = lexical_cast<int>(si.attributes[11]);

  _father = father;
  _startValidationFrame = -1;
  _type = WRONG_NEXT;
}

FixationWindow::FixationWindow(const ShapeInfo& si,
                               VariableManager& vm,
                               Trial* father)
{
  assert(si.attributes.size() == 12);
  assert(father);
  _name = si.attributes[0];
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(si.attributes[5]));
  vm.addVariable(_G = new Variable(si.attributes[6]));
  vm.addVariable(_B = new Variable(si.attributes[7]));
  vm.addVariable(_width = new Variable(si.attributes[8]));
  vm.addVariable(_height = new Variable(si.attributes[9]));
  vm.addVariable(_validationNbFrame = new Variable(si.attributes[10]));

  _ttl = lexical_cast<int>(si.attributes[11]);

  _father = father;
  _startValidationFrame = -1;
  _type = WAITING_FIXATION;
}

// Small design flaw here : neutral window
// has a _validationNbFrame field inherited from Window but doesn't use it . . .
// sorry about that !
NeutralWindow::NeutralWindow(const ShapeInfo& si,
                             VariableManager& vm,
                             Trial* father)
{
  assert(si.attributes.size() == 11);
  assert(father);
  _name = si.attributes[0];
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(si.attributes[5]));
  vm.addVariable(_G = new Variable(si.attributes[6]));
  vm.addVariable(_B = new Variable(si.attributes[7]));
  vm.addVariable(_width = new Variable(si.attributes[8]));
  vm.addVariable(_height = new Variable(si.attributes[9]));
  vm.addVariable(_validationNbFrame = new Variable(0));

  _ttl = lexical_cast<int>(si.attributes[10]);

  _father = father;
  _startValidationFrame = -1;
  _type = NEUTRAL;
}

void
Window::react2input(Status& s,
                    datas& ds,
                    int n,
                    ms displayTime)
{
  double x = ds[0].volt;
  double y = ds[1].volt;

  if (isIn(x, y))
  {
    if (_startValidationFrame == -1)
    {
      if (n - _startValidationFrame > _validationNbFrame->value)
        s[_type] = true;
    }
    else
      _startValidationFrame = n;
  }
  else
    _startValidationFrame = -1;

  Shape::react2input(s, ds, n, displayTime);
}
