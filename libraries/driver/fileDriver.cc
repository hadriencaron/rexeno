/**
 * @file   fileDriver.cc
 * @author hadrien <hadrien@barbow>
 * @date   Sat Nov 30 18:39:55 2013
 * 
 * @brief  Implementation of the driver for a project
 * where the input comes from a datafile
 * This uses non-real time functions so it works on a
 * regular non-xenomai computer. But we should not expect
 * exact replication of the results of a xenomai system.
 * Exact behaviour replication will be done later by another driver.
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include "driver.hh"
#include "session.hh"

FileDriver::FileDriver(Session* father,
                       Calibration* cal,
                       std::string filename)
  : Driver::Driver(father, cal)
{
  // Set Inital time
  timeb tb;
  ftime(&tb);
  _start = tb.millitm + (tb.time & 0xfffff) * 1000;
  // Init File
  _infile.open("infile.txt");
}

/** 
 * @return time since initialization
 */
ms
FileDriver::GetTime()
{
  // Get time by differenciating with Initial value
  timeb tb;
  ftime(&tb);
  ms current = tb.millitm + (tb.time & 0xfffff) * 1000;

  return (current - _start);
}

void
FileDriver::AnalogIn(datas& data)
{
  PDEBUG("FileDriver::AnalogIn ", "start");
  channel Xs = data[0];
  channel Ys = data[1];
  channel::iterator it;

  // Get time by differenciating with Initial value
  timeb tb;
  ftime(&tb);
  ms current = tb.millitm + (tb.time & 0xfffff) * 1000;

  for (it = Xs.begin(); it != Xs.end(); ++it)
  {
    _infile >> it->volt;
    it->timing = current;
  }
  for (it = Ys.begin(); it != Ys.end(); ++it)
  {
    _infile >> it->volt;
    it->timing = current;
  }

  // unsigned int i = 0;
  // while (!_infile.eof())
  // {
  //   _infile >> data[i].timing;
  //   _infile >> data[i].volt;
  //   ++i;
  //   // getline(infile, sLine);
  //   // cout << sLine << endl;
  // }

  // for (i = 0; size && (i < data.size()); ++i)
  // {
  //   data[i].volt = _analogData[2 * i];
  //   data[i].timing = _analogData[2 * i + 1];
  // }

}
