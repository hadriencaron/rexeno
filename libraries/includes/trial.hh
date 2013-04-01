#ifndef	TRIAL_HH_
# define TRIAL_HH_

# include <set>
# include <string>
# include "parser.hh"
# include "shape.hh"
# include "square.hh"
# include <GL/glut.h>

using namespace std;
using namespace configuration;
class Shape;
class Square;

class Trial
{
public:
  Trial(TrialInfo& ti);
  ~Trial();

  string run();
private:
  void makeShapes();
  set<Shape*> _shapes;
};


#endif
