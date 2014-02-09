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
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

FileDriver::FileDriver(Session* father,
                       Calibration* cal,
                       std::string filename)
  : Driver::Driver(father, cal)
{
  _ofs = new ofstream("/tmp/Eye", std::ofstream::out);
  // Set Inital time
  timeb tb;
  ftime(&tb);
  _start = tb.millitm + (tb.time & 0xfffff) * 1000;
  // Init File
  PDEBUG("FileDriver::FileDriver ", "open file file : " << filename);
  _infile.open(filename.c_str(), std::ifstream::in);
  if (!_infile.good())
  {
    cerr << "Error: Failed to open file ... already opened ?" << endl;
    throw;
  }
  if (_infile.eof())
  {
    cerr << "Error: file is empty" << endl;
    throw;
  }
}

void
FileDriver::InitTime()
{
  // Set Inital time
  timeb tb;
  ftime(&tb);
  _start = tb.millitm + (tb.time & 0xfffff) * 1000;
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

int
FileDriver::AnalogIn(datas& data)
{
  PDEBUG("FileDriver::AnalogIn ", "start");
  channel& Xs = data[0];
  channel& Ys = data[1];
  PDEBUG("FileDriver::AnalogIn ", "size channel 0 : " << Xs.size());

  // Get time by differenciating with Initial value
  timeb tb;
  ftime(&tb);
  ms current = tb.millitm + (tb.time & 0xfffff) * 1000 - _start;
  std::string sLine;
  if (getline(_infile, sLine))
  {
    vector<string> strs;
    vector<string>::iterator it;
    boost::split(strs,sLine,boost::is_any_of("\t "), boost::token_compress_on);
    for (it = strs.begin(); it != strs.end(); ++it)
    {
      if (*it != "")
      {
        Xs[0].volt = boost::lexical_cast<double>(*it);
        Xs[0].timing = current;
        ++it;
        Ys[0].volt = boost::lexical_cast<double>(*it);
        Ys[0].timing = current;
      }
    }
    return (strs.size());
  }
  else
  {
    cout << "end of input" << endl;
    throw;
  }
}
