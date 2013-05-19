#ifndef SESSION_HH_
# define SESSION_HH_

# include <iostream>
# include <list>
# include <GL/glut.h>

# include "parser.hh"
# include "trial.hh"
# include "setup.hh"
# include "recorder.hh"
# include "driver.hh"

using namespace std;
using namespace configuration;

// Singleton class
class Session
{
public:
  ~Session();
  static Session* GetInstance();
  static Session* GetInstance(SessionInfo& s,
		  	  	  	  	  	    vector<int>& t);
  void run(int argc,
           char** argv);
  void DisplayFrame();
  void DisplayHeader();

  void (*afterTrial)(string&, VariableManager&, int);
  void (*beforeTrial)(string&, VariableManager&);
  void SetDriver(Driver* d) {_driver = d;}

  Setup* setup;
  Recorder* recorder;
  //void (*interFrame)(VariableManager&);
  //void (*ConfigurableWindow)(TrialManager *);
  int NbFrame4init() {return _nbFrame4init;}
  int NbInitFrames() {return _nbInitFrames;}
  ms GetTime();
  bool Initialized();
private:
  Session(SessionInfo& s,
		  vector<int>&);
  void _FillData();

  Driver* _driver;
  vector<Trial*> _trials;
  static Session* _instance;
  vector<pair<double, ms> > _inputData;
  vector<Trial*>::iterator _currentTrial;
  // Background Color :
  int _R, _G, _B;
  // Guardian Trial : in charge of
  // evaluating the offset value of display
  bool _initialized;
  int _nbFrame4init;
  int _nbInitFrames;
  double _offsetVsync; // offset between 0 and 16.666 (if 60Hz)
};


#endif

