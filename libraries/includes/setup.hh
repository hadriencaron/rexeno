#ifndef SETUP_HH_
# define SETUP_HH_

# include "setup.hh"

class Setup
{
public:
  Setup(string confFile = "~/.rexeno");

  double xRatio();
  double yRatio() {return 1;}
private:
  // centimenters
  double _screenHeight;
  double _screenWidth;
};


#endif

