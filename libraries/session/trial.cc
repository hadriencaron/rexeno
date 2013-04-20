#include "trial.hh"

Trial::Trial(TrialInfo& ti)
  : _curFrameId(0),
    _nbFrames(1),
    _name(ti.name)
{
  vector<ShapeInfo>::iterator it;
  for (it = ti.shapes.begin(); it != ti.shapes.end(); ++it)
  {
    Shape *newShape = NULL;
    if (it->name == "Square")
      newShape = new Square(*it, variables);
    if (newShape)
    {
      _shapes.push_back(newShape);
      if (newShape->frameEnd() > _nbFrames)
        _nbFrames = newShape->frameEnd();
      _ttlFrames[newShape->frameStart()] = newShape->ttl();
    }
  }

  _status[RUNNING] = true;
  _status[PAUSE] = false;
  _status[WRONG_REDO] = false;
  _status[WRONG_NEXT] = false;
  _status[CORRECT] = false;
  _status[WAITING_FIXATION] = false;
}

Trial::~Trial()
{
  vector<Shape*>::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    delete curShape;
  }
}

int
Trial::displayFrame(Driver& d)
{
  vector<Shape*>::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    glPushMatrix();
    glTranslatef(0.5, 0, 0);
    curShape->display();
    glPopMatrix();

    if (curShape->monitorDisplayable())
    {
      glPushMatrix();
      glTranslatef(-0.5, 0, 0);
      curShape->displayMonitor();
      glPopMatrix();
    }
  }
  glutSwapBuffers();
  glutPostRedisplay();
  glClear(GL_COLOR_BUFFER_BIT);

  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    curShape->react2input(_status);
  }
  return (_react2status());
}

int
Trial::_react2status()
{
  if (_status[WAITING_FIXATION] == true)
  {
    return (WAITING_FIXATION);
  }

  if (_status[CORRECT] == true)
  {
    return (CORRECT);
  }

  if (_status[WRONG_NEXT] == true)
  {
    return (WRONG_NEXT);
  }

  if (_status[WRONG_REDO] == true)
  {
    return (WRONG_REDO);
  }

  if (_status[PAUSE] == true)
  {
    return (PAUSE);
  }

  if (_status[RUNNING] == true)
  {
    _curFrameId++;
    return (RUNNING);
  }
  return (WRONG_NEXT); // should not get here
}

void
Trial::adjustNbFrames()
{
  vector<Shape*>::iterator it;

  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    double curEndFrame = (*it)->frameEnd();

    if (curEndFrame > _nbFrames)
      _nbFrames = curEndFrame;
  }
}

bool
Trial::finished()
{
  return (_curFrameId > _nbFrames);
}

bool
Trial::atStart()
{
  return (_curFrameId == 0);
}

void
Trial::reset()
{
  _curFrameId = 0;
}
