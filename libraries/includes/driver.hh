#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <vector>
# include "calibration.hh"
# include "types.hh"

class Driver
{
public:
  Driver() {}
  virtual ~Driver() {}

  virtual ms getTime() = 0;
  virtual void analogIn(datas& data) = 0;
  virtual void ttlPulse(uint value,
                        ms delay = 0,
                        ms duration = 5) {}
  virtual void analogOut(double volt,
                         ms delay = 0,
                         ms duration = 5) {}
  virtual void react2input() = 0 ;
  
protected:
  string _name;
  Calibration* _calibration;
};

#include <iostream>
using namespace std;
#include <cstdlib>
#include <sys/timeb.h>

class DummyDriver : public Driver
{
public:
  DummyDriver();
  ~DummyDriver() {}

  ms getTime();
  void react2input();
  void analogIn(datas&);
private:
  ms _start;
};

#endif
