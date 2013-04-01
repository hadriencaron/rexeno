#include "trial.hh"

Trial::Trial(TrialInfo& ti)
{
  std::vector<ShapeInfo>::iterator it;

  for (it = ti.shapes.begin(); it != ti.shapes.end(); ++it)
  {
    Shape *newShape = NULL;
    if (it->name == "Square")
      newShape = new Square(*it);
    _shapes.insert(newShape);
  }
}

Trial::~Trial()
{
  set<Shape*>::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    delete curShape;
  }
}

string
Trial::run()
{
  set<Shape*>::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    curShape->display();

  }

  glutSwapBuffers();
  glutPostRedisplay();
  glClear(GL_COLOR_BUFFER_BIT);

  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    curShape->react2input();

  }
  return ("");
}
