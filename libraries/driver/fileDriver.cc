/**
 * @file   fileDriver.cc
 * @author hadrien <hadrien@barbow>
 * @date   Sat Nov 30 18:39:55 2013
 * 
 * @brief  Implementation of the driver for a project
 * where the input comes from a datafile
 * 
 */

#include <iostream>
#include <fstream>
#include <string>


FileDriver::FileDriver(std::string filename)
   : _infile.open("infile.txt");
{
  _calibration = new KeyboardCalibration();
  
}

void
FileDriver::AnalogIn(datas& ds)
{



}
