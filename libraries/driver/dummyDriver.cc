#include "dummyDriver.hh"

DummyDriver::DummyDriver()
{
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

