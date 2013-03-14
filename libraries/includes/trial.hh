#ifndef	TRIAL_HH_
# define TRIAL_HH_

# include <set>
# include <string>

using namespace std;
class Shape;

class Trial
{
public:
  Trial();
  ~Trial();

  string run();
private:
  set<Shape*> _shapes;
};


#endif
