#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <vector>
# include "session.hh"


class Driver
{
public:
  Driver() {}
  virtual ~Driver() {}

  virtual ms getTime() = 0;
  virtual void analogIn(datas& data) {}
  virtual void ttlPulse(uint value,
                        ms delay = 0,
                        ms duration = 5) {}
  virtual void analogOut(double volt,
                         ms delay = 0,
                         ms duration = 5) {}
protected:
  string _name;
};

#endif
