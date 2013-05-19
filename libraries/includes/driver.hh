#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <native/buffer.h>
# include <vector>
# include "calibration.hh"
# include "types.hh"
# include "recorder.hh"

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
  void setRecorder(Recorder* r) {_recorder = r;}
  
protected:
  string _name;
  Calibration* _calibration;
  Recorder* _recorder;
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


#ifdef XENO

#include <native/mutex.h>

class XenoDriver : public Driver
{
public:
  XenoDriver();
  ~XenoDriver() {}

  ms getTime();
  void react2input();
  void analogIn(datas&);
private:
  int _initNidaqCard();
  int _launch();

  ms _start;
  double* _analogData;

  RT_MUTEX* _mutex;
  RT_BUFFER* _buffer;
};

#endif /* XENO */

#endif /* DRIVER_HH_ */
