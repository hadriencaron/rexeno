#include "trial.hh"
#include "driver.hh"
#include "setup.hh"

#include <boost/foreach.hpp>
#include <iostream>
#include <fstream>


Trial::Trial(TrialInfo& ti,
             Session* father)
  : _curFrameId(0),
    _nbFrames(ti.max_duration),
    _name(ti.name),
    _father(father)
{
  PDEBUG("Trial::Trial ", "trial " << _name << " length set to " << _nbFrames);
  _logged = false;
  // _data.resize(8 * 20); // 8 channels x 20 samples (20 > 16.666)

  _data.resize(8); // 8 channels
  vector<channel>::iterator dataIt;
  for (dataIt = _data.begin(); dataIt != _data.end(); ++dataIt)
  {
    (*dataIt) = vector<Element>(20); // 20 samples per channel
  }

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
      // if (newShape->frameEnd() > _nbFrames)
      //   _nbFrames = newShape->frameEnd();
    }
  }

  _ttl = new vector<TtlEvent*>;
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );

  if (father->_enableReplay)
    replayerLogs.open("replayerLogs");
}

Trial::~Trial()
{
  if (_father->_enableReplay)
    replayerLogs.close();
  vector<Shape*>::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    delete curShape;
  }
}

int
Trial::displayFrame(Driver* driver)
{
  int nbInput;

  if (_nbFrames <= _curFrameId)
  {
    PDEBUG("Trial::displayFrame", "Time up, resquest reset");
    Setup::reset();
    _status[WRONG_NEXT] = true;
    glutSwapBuffers();
    glutPostRedisplay();
    glClear(GL_COLOR_BUFFER_BIT);
    PDEBUG("Trial::displayFrame", " displayed frame number : " << _curFrameId << " / " << _nbFrames);
    return WRONG_NEXT;
  }

  _status[RUNNING] = true;
  _status[PAUSE] = false;
  _status[WRONG_REDO] = false;
  _status[WRONG_NEXT] = false;
  _status[CORRECT] = false;
  _status[WAITING_FIXATION] = false;
  _status[NEUTRAL] = false;
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
  PDEBUG("Trial::displayFrame", " displayed frame number : " << _curFrameId << " / " << _nbFrames);

  _sendTtls(driver);
  //_status[RUNNING] = false;
  driver->React2input();
  nbInput = driver->AnalogIn(_data);
  ms displayTime = driver->GetTime();

  if (_father->_enableReplay)
    _log(_data, nbInput);
  if ((_curFrameId == 0) && (!_logged))
  {
    s->recorder->Save("TrialStart_ " + lexical_cast<string>(displayTime), "events.txt");
    s->recorder->Save(_name + lexical_cast<string>(displayTime), "events.txt");
    _logged = true;
  }
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

    PDEBUG("Trial::displayFrame ", curShape->name() << " f " << curShape->frameStart() << " t " << curShape->frameEnd() << " d " << curShape->Displayable(_curFrameId));
    if (curShape->Displayable(_curFrameId))
      curShape->React2input(_status, _data, nbInput, _curFrameId, driver->GetTime());
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
    PDEBUG("Trial::_react2status ", "CORRECT");
    return (CORRECT);
  }

  if (!_status[NEUTRAL])
  {
    if (_status[WRONG_NEXT] == true)
    {
      PDEBUG("Trial::_react2status ", "WRONG_NEXT");
      return (WRONG_NEXT);
    }

    if (_status[WRONG_REDO] == true)
    {
      PDEBUG("Trial::_react2status ", "WRONG_REDO");
      return (WRONG_REDO);
    }
  }
  if (_status[PAUSE] == true)
  {
    PDEBUG("Trial::_react2status ", "PAUSE");
    return (PAUSE);
  }

  if (_status[WAITING_FIXATION] == true)
  {
    _curFrameId++;
    PDEBUG("Trial::_react2status ", "WAITING_FIXATION");
    return (RUNNING);
  }

  if (_status[RUNNING] == true)
  {
    _curFrameId++;
    PDEBUG("Trial::_react2status ", "RUNNING");
    return (RUNNING);
  }
  PDEBUG("Trial::_react2status ", "bug here");
  return (WRONG_NEXT); // should not get here (this line is to avoid a compiler warning)
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
Trial::Reset()
{
  PDEBUG("Trial::Reset ", "start");
  _curFrameId = 0;
  Status::iterator it;
  for (it = _status.begin(); it != _status.end(); ++it)
  {
    it->second = false;
  }
  PDEBUG("Trial::Reset ", "end");
  // Shapes::iterator shapesIterator;
  // for (shapesIterator = _shapes.begin(); shapesIterator != _shapes.end(); ++shapesIterator)
  // {
  //   (*shapesIterator)->Reset();
  // }
}

bool
Trial::status(int key)
{
  return _status[key];
}

void
Trial::_log(datas& d,
            int nbInput)
{
  channel& Xs = d[0];
  channel& Ys = d[1];
  int i;

  for (i = 0; i < nbInput; ++i)
  {
    replayerLogs << Xs[i].volt << " " << Ys[i].volt << " ";
  }
  replayerLogs << std::endl;
}
