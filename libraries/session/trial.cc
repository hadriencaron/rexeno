#include "trial.hh"
#include "driver.hh"
#include "setup.hh"

#include <boost/foreach.hpp>

Trial::Trial(TrialInfo& ti)
  : _curFrameId(0),
    _nbFrames(1),
    _name(ti.name),
    _displayTime(0),
    _start(true)
{
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
	if (it->name == "Sphere")
		newShape = new Sphere(*it, variables, this);
	if (it->name == "Plan")
		newShape = new Plan(*it, variables, this);

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
Trial::displayFrame(Driver* driver)
{
  if (_displayTime==0){
	  _displayTime = driver->GetTime();
  }
  Session* s = Session::getInstance();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float Sun =  0.5f;

  GLfloat lightPosition[4] = {0.0f,0.0f,0.0f,1.0f};
  GLfloat lightAmbient[4] = {Sun,Sun,Sun,2.0f};
  GLfloat lightDiffuse[4] = {1.0f,1.0f,1.0f,1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  gluLookAt(0,1,1.8, 0,0,0, 0,1,0);

  vector<Shape*>::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;
    glPushMatrix();
    //glTranslatef(0.5, 0, 0);
    if (curShape->Displayable(_curFrameId)){
    	if (curShape->name()=="Sphere"){
        	curShape->Display();
        	if (curShape->getIsWorking()==false){
        		 // std::cout << "Time > "<< (driver->GetTime()-_displayTime) << endl;
        	}
    	}
    	else{
    		curShape->Display();
    	}
    }
  //  std::cout << "Time > "<< (driver->GetTime()-_displayTime) << endl;
    glPopMatrix();

    if (curShape->id() != 7){
		if (curShape->MonitorDisplayable())
		{
			glPushMatrix();
			//glTranslatef(-0.5, 0, 0);
			if (curShape->Displayable(_curFrameId))
				curShape->DisplayMonitor();
			glPopMatrix();
		}
    }

  }

  glutSwapBuffers();
  glutPostRedisplay();
  glClear(GL_COLOR_BUFFER_BIT);

 // PDEBUG("Trial::displayFrame", " displayed frame " << _curFrameId);

  _sendTtls(driver);

  driver->React2input();
  driver->AnalogIn(_data);
  ms displayTime = driver->GetTime();

  if((_curFrameId == 0) && (_start)){
		for (it = _shapes.begin(); it != _shapes.end(); ++it)
		{
		  Shape *curShape = *it;

		  if ((_curFrameId == 0) && (!_logged))
		  {
			s->recorder->Save(curShape->getAttrsToString() ,"events.txt");
		  }

	    }
	    _start = false;
		s->recorder->Save("" ,"events.txt");
  }

  if ((_curFrameId == 0) && (!_logged))
  {
	    s->recorder->Save("TrialStart_ " + lexical_cast<string>(displayTime), "events.txt");
	    s->recorder->Save(_name + ' ' + lexical_cast<string>(displayTime) + "\n", "events.txt");

    _logged = true;
  }


  if (_data[0][0].rep != (-1)){
	  	printf("J'ai une réponse! => %d \n", _data[0][0].rep);
		string str;
		ostringstream ostr;
		ostr << "Subject says : " << _data[0][0].rep;
		str = ostr.str();
		s->recorder->Save(str, "events.txt");
	  _status[CORRECT] = true;
  }

  for (it = _shapes.begin(); it != _shapes.end(); ++it)
  {
    Shape *curShape = *it;

		if ((_curFrameId == 0) && (!_logged))
		{
			s->recorder->Save(curShape->getAttrsToString() ,"events.txt");
		}

	   //PDEBUG("Trial::displayFrame ", curShape->name() << " f " << curShape->frameStart() << " t " << curShape->frameEnd() << " d " << curShape->Displayable(_curFrameId));
		if (curShape->Displayable(_curFrameId)){
				curShape->React2input(_status, _data, _curFrameId, driver->GetTime());

		}
//	std::cout << "String => " << curShape->getAttrsToString() << " X  => " << curShape->x() << endl ;
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
   // PDEBUG("Trial::_react2status ", "RUNNING");
    return (RUNNING);
  }
  PDEBUG("Trial::_react2status ", "bug here");
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
Trial::Reset(Driver *d)
{
//  PDEBUG("Trial::Reset ", "start")
  _curFrameId = 0;
  _logged = false; 											// !!
  Status::iterator it;
  for (it = _status.begin(); it != _status.end(); ++it)
  {
    it->second = false;
  }
  d->Reset();
  Shapes::iterator shapesIterator;
  for (shapesIterator = _shapes.begin(); shapesIterator != _shapes.end(); ++shapesIterator)
   {
	  (*shapesIterator)->Reset();
	  _displayTime = d->GetTime();
   }

}

bool
Trial::status(int key)
{
  return _status[key];
}
