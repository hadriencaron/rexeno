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
 * the dummy driver uses a keyboard calibration
 * which is a pretentious way of saying that the user
 * can control the input through the keyboard keys zqsd
 * 
 */
DummyDriver::DummyDriver(Session* father,
                         Calibration* cal)
  :  Driver::Driver(father, cal),
     _ofs("/tmp/Eye", std::ofstream::out)
{
  _calibration = new KeyboardCalibration();
  _name = "dummy";
  _father = father;

  // Set initial time
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
  // Get time by differenciating with Initial value
  timeb tb;
  ftime(&tb);
  ms current = tb.millitm + (tb.time & 0xfffff) * 1000;

  return (current - _start);
}

/** 
 * Use the data to change calibration
 * 
 */
void
DummyDriver::React2input()
{
  if (_calibration)
    _calibration->React2input();
}

/** 
 * Gets the keyboard input through calibration
 * 
 * @param data 
 */
int
DummyDriver::AnalogIn(datas& data)
{
  _calibration->adjustPoint(data);
  return (1);
}

