#include "driver.hh"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <sys/timeb.h>

class DummyDriver : public Driver
{
public:
  DummyDriver();
  ~DummyDriver() {}

  ms getTime();
private:
  ms _start;
};
