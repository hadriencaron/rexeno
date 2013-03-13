#include "session.hh"
#include "trial.hh"

Session::Session(sessionInfo &s)
  : _info(s)
{
  vector<trialInfo>::iterator it;

  for (it = _info.trials.begin(); it != _info.trials.end(); ++it)
    {
      cout << "should create a trial here" << endl;
    }
}

Session::~Session()
{

}

void
Session::run()
{
  vector<Trial*>::iterator it;
  string b;

  for (it = _trials.begin(); it != _trials.end(); ++it)
    {
      do
	{
	  b = (*it)->run();
	}
      while (b == "WRONG_REDO");
    }
}

