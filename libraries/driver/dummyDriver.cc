#include "driver.hh"

DummyDriver::DummyDriver()
{
  _calibration = new KeyboardCalibration();
  _name = "dummy";

  timeb tb;
  ftime(&tb);
  _start = tb.millitm + (tb.time & 0xfffff) * 1000;
}

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

