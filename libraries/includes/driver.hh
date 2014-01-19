/**
 * @file   driver.hh
 * @author hadrien <hadrien@barbow>
 * @date   Sun Jun 30 01:49:32 2013
 * 
 * @brief  Driver(s) declaration(s) file
 * The Driver is an abstract class that describes the link
 * between a protocole (the computer) and the subject (the outside world)
 * This class contains functions to get information from the outside world about
 * - time elapsing in milliseconds
 * - getting and setting analog channels (in Volts)
 * - getting and setting digital channels (up/down on each bit)
 *
 * Currently available implementations :
 * - XenoDriver : with a nidaq card (todo? : remove keyboard)
 * - DummyDriver : just the keyboard (todo : )
 * - FileDriver
 */
#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <vector>
# include "calibration.hh"
# include "types.hh"
# include "recorder.hh"

class Session;

/// Abstract Driver
class Driver
{
public:
  Driver(Session*, Calibration*);
  virtual ~Driver() {}

  virtual ms GetTime() = 0;
  // Driver fills data with n values. Returns n
  virtual int AnalogIn(datas& data) = 0;
  virtual void TtlPulse(uint value,
                        ms delay = 0,
                        ms duration = 5) {}
  virtual void AnalogOut(double volt,
                         ms delay = 0,
                         ms duration = 5) {}
  virtual void React2input() = 0 ;
  void SetRecorder(Recorder* r) {_recorder = r;}
  
protected:
  string _name;
  Calibration* _calibration;
  Recorder* _recorder;
  Session* _father;
};

#include <iostream>
using namespace std;
#include <cstdlib>
#include <sys/timeb.h>

class DummyDriver : public Driver
{
public:
  DummyDriver(Session*,
              Calibration*);
  ~DummyDriver() {}

  ms GetTime();
  void React2input();
  int AnalogIn(datas&);
private:
  ms _start;
  ofstream _ofs;
};

class FileDriver : public Driver
{
public:
  FileDriver(Session*,
             Calibration*,
             std::string);
  ~FileDriver() {}

  ms GetTime();
  void React2input() {}
  int AnalogIn(datas&);
private:
  ms _start;
  ifstream _infile;
  ofstream* _ofs;
};

#ifdef XENO

# include <native/mutex.h>
# include <native/buffer.h>

class XenoDriver : public Driver
{
public:
  XenoDriver();
  ~XenoDriver() {}

  ms GetTime();
  void React2input();
  int AnalogIn(datas&);
private:
  int _initNidaqCard();
  int _launch();

  ms _start;
  double* _analogData;

  RT_MUTEX* _mutex;
  RT_BUFFER* _recorderBuffer;
  RT_BUFFER* _displayBuffer;
};

#endif /* XENO */

#endif /* DRIVER_HH_ */
