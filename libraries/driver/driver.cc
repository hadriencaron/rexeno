#include "driver.hh"
#include "session.hh"

Driver::Driver(Session* father,
               Calibration* cal)
{
  PASSERT(father && cal);

  _father = father;
  _calibration = cal;
}

