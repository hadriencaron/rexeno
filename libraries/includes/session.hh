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
# include <vector>
# include <list>
# include "types.hh"

class Driver;
class VariableManager;
class Variable;
class Trial;
class Setup;
class Recorder;
class Order;
class Calibration;

namespace configuration
{
  class SessionInfo;
};

using namespace std;

// Singleton class
class Session
{
public:
  friend class Trial;
  ~Session();
  static Session* getInstance();
  static Session* getInstance(configuration::SessionInfo& s,
                              Order& o);
  void run(int argc,
           char** argv);
  void displayFrame();
  void displayHeader();

  void (*afterTrial)(std::string&, VariableManager&, int);
  void (*beforeTrial)(std::string&, VariableManager&);
  void setDriver(Driver* d) {_driver = d;}

  Setup* setup;
  Recorder* recorder;
  //void (*interFrame)(VariableManager&);
  //void (*ConfigurableWindow)(TrialManager *);
  int nbFrame4init() {return _nbFrame4init;}
  int nbInitFrames() {return _nbInitFrames;}
  ms getTime();
  bool initialized();
  Calibration* CalibrationCreator(std::string);
  Driver* DriverCreator(std::string,
                        Calibration*);

private:
  Session(configuration::SessionInfo& s,
          Order& o);
  void _fillData();

  std::vector<Trial*> _trialsDefinitions;
  std::vector<int> _trialsOrder;
  static Session* _instance;
  std::vector<pair<double, ms> > _inputData;
  std::vector<int>::iterator _currentTrial;
  // Background Color :
  int _R, _G, _B;
  // Guardian Trial : in charge of
  // evaluating the offset value of display
  bool _initialized;
  int _nbFrame4init;
  int _nbInitFrames;
  double _offsetVsync; // offset between 0 and 16.666 (if 60Hz)

#ifdef DEBUG
  int __debug_FrameNumber;
#endif
  std::string _name;
  int _x_channel;
  int _y_channel;
  std::string _driverType;
  std::string _coordinates_type;
  bool _enableReplay;
  Driver* _driver;
};

#ifdef DEBUG
# define PDEBUG(fmt, args) cerr << fmt << args << "\n";
# define PASSERT(cond) assert(cond);
#else
# define PDEBUG(fmt, args) /* not debugging: nothing */
# define PASSERT(cond)
#endif


#endif

