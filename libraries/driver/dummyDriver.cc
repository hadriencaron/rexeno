/**
 * @file   dummyDriver.cc
 * @author hadrien <hadrien@barbow>
 * @date   Sun Jun 30 01:55:38 2013
 * 
 * @brief  Implementation of the Driver for a computer
 * that doesn't have xenomai or a nidaq card.
 * 
 * TODO : adapt this class to be able to use a mouse to emulate Eye movements !
 */


#include "driver.hh"



/** 
 * Constructor : just  initialization of driver
 * 
 */
DummyDriver::DummyDriver()
{
  _calibration = new KeyboardCalibration();
  _name = "dummy";

  timeb tb;
  ftime(&tb);
  _start = tb.millitm + (tb.time & 0xfffff) * 1000;
}

/** 
 * @return time since initialization
 */
ms
DummyDriver::GetTime()
{
  timeb tb;
  ftime(&tb);
  ms current = tb.millitm + (tb.time & 0xfffff) * 1000;

  return (current - _start);
}

void
DummyDriver::React2input()
{
  if (_calibration)
    _calibration->react2input();
}

void
DummyDriver::AnalogIn(datas& data)
{
  _calibration->adjustPoint(data);
}

