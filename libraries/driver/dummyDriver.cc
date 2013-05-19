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
DummyDriver::getTime()
{
  timeb tb;
  ftime(&tb);
  ms current = tb.millitm + (tb.time & 0xfffff) * 1000;

  return (current - _start);
}

void
DummyDriver::react2input()
{
  if (_calibration)
    _calibration->react2input();
}

void
DummyDriver::analogIn(datas& data)
{
  _calibration->adjustPoint(data);
}

