#include "trial.hh"
#include "driver.hh"
#include <boost/foreach.hpp>

Trial::Trial(TrialInfo& ti)
  : _curFrameId(0),
    _nbFrames(1),
    _name(ti.name)
{
  _logged = false;
  _data.resize(8);
  vector<ShapeInfo>::iterator it;
  for (it = ti.shapes.begin(); it != ti.shapes.end(); ++it)
  {
    Shape *newShape = NULL;
    if (it->name == "Square")
      newShape = new Square(*it, variables, this);
    if (it->name == "Cross")
      newShape = new Cross(*it, variables, this);
    if (it->name == "WrongWindow")
      newShape = new WrongWindow(*it, variables, this);
    if (it->name == "CorrectWindow")
      newShape = new CorrectWindow(*it, variables, this);
    if (it->name == "NeutralWindow")
      newShape = new NeutralWindow(*it, variables, this);
    if (it->name == "FixationWindow")
      newShape = new FixationWindow(*it, variables, this);
    if (newShape)
    {
      _shapes.push_back(newShape);
      if (newShape->frameEnd() > _nbFrames)
        _nbFrames = newShape->frameEnd();
    }
  }

  _status[RUNNING] = true;
  _status[PAUSE] = false;
  _status[WRONG_REDO] = false;
  _status[WRONG_NEXT] = false;
  _status[CORRECT] = false;
  _status[WAITING_FIXATION] = false;
  _status[NEUTRAL] = false;

  _ttl = new vector<TtlEvent*>;
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );
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
Trial::displayFrame(Driver* d)
{
  Session* s = Session::getInstance();

  vector<Shape*>::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;
    glPushMatrix();
    glTranslatef(0.5, 0, 0);
    if (curShape->Displayable(_curFrameId))
      curShape->Display();
    glPopMatrix();

    if (curShape->MonitorDisplayable())
    {
      glPushMatrix();
      glTranslatef(-0.5, 0, 0);
      if (curShape->Displayable(_curFrameId))
        curShape->DisplayMonitor();
      glPopMatrix();
    }
  }
  glutSwapBuffers();
  glutPostRedisplay();
  glClear(GL_COLOR_BUFFER_BIT);

  _sendTtls(d);
  _status[RUNNING] = false;
  d->React2input();
  d->AnalogIn(_data);
  ms displayTime = d->GetTime();

  if ((_curFrameId == 0) && (!_logged))
  {
    s->recorder->Save("TrialStart_ " + lexical_cast<string>(displayTime), "events.txt");
    s->recorder->Save(_name + lexical_cast<string>(displayTime), "events.txt");
    _logged = true;
  }
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    if (curShape->Displayable(_curFrameId))
      curShape->react2input(_status, _data, _curFrameId, d->GetTime());
  }
  Setup::reset();
  return (_react2status());
}

void
Trial::_sendTtls(Driver* d)
{
  vector<TtlEvent*>::iterator it;
  for (it = _ttl->begin(); it != _ttl->end(); ++it)
  {
    if ((*it)->value != 0)
      d->TtlPulse((*it)->value, (*it)->delay);
  }
}

int
Trial::_react2status()
{

  if (_status[CORRECT] == true)
  {
    return (CORRECT);
  }

  if (!_status[NEUTRAL])
  {
    if (_status[WRONG_NEXT] == true)
    {
      return (WRONG_NEXT);
    }

    if (_status[WRONG_REDO] == true)
    {
      return (WRONG_REDO);
    }
  }
  if (_status[PAUSE] == true)
  {
    return (PAUSE);
  }

  if (_status[WAITING_FIXATION] == true)
  {
    return (RUNNING);
  }

  if (_status[RUNNING] == true)
  {
    _curFrameId++;
    return (RUNNING);
  }
  return (WRONG_NEXT); // should not get here (this line is to avoid a compiler warning)
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

bool
Trial::status(int key)
{
  return _status[key];
}

