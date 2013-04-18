#ifndef SESSION_HH_
# define SESSION_HH_

# include <iostream>
# include <list>

# include "parser.hh"
# include "trial.hh"
# include "setup.hh"
# include <GL/glut.h>

typedef unsigned long long ms;
using namespace std;
using namespace configuration;
class Trial;
class Driver;

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

  void (*afterTrial)(string&, VariableManager&, int);
  void (*beforeTrial)(string&, VariableManager&);
  void setSetup(Setup* s);
  
  Setup* setup;
  //void (*interFrame)(VariableManager&);
  //void (*ConfigurableWindow)(TrialManager *);
  
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
};


#endif

