/**
 * @file   session.hh
 * @author hadrien <hadrien@barbow>
 * @date   Tue May 21 23:07:59 2013
 * 
 * @brief  Defines the Session class
 * This is a global unique object (Design Pattern Singleton)
 * it represents a complete session.
 * The main task of about any program is to run each trial of the session class.
 * 
 */

#ifndef SESSION_HH_
# define SESSION_HH_

# include <iostream>
# include <list>

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
  static Session* getInstance();
  static Session* getInstance(SessionInfo& s);
  void run(int argc,
           char** argv);
  void displayFrame();
  void displayHeader();

  void (*afterTrial)(string&, VariableManager&, int);
  void (*beforeTrial)(string&, VariableManager&);
  void setDriver(Driver* d) {_driver = d;}

  Setup* setup;
  Recorder* recorder;
  //void (*interFrame)(VariableManager&);
  //void (*ConfigurableWindow)(TrialManager *);
  int nbFrame4init() {return _nbFrame4init;}
  int nbInitFrames() {return _nbInitFrames;}
  ms getTime();
  bool initialized();
private:
  Session(SessionInfo& s);
  void _fillData();

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

