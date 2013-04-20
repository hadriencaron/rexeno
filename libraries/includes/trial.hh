#ifndef	TRIAL_HH_
# define TRIAL_HH_

# include <map>
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

# define RUNNING 0
# define PAUSE 1
# define WRONG_REDO 2
# define WRONG_NEXT 3
# define CORRECT 4
# define WAITING_FIXATION 5


class Trial
{
public:
  Trial(TrialInfo& ti);
  ~Trial();
  int displayFrame();
  bool finished();
  bool atStart();
  string& name() {return _name;}
  void reset();
  void adjustNbFrames();

  int frameEnd() {return _nbFrames;}
  VariableManager variables;
private:
  int _react2status();
  
  int _curFrameId;
  int _nbFrames;
  Status _status;
  vector<Shape*> _shapes;
  string& _name;
  int _argc;
  char **_argv;
};


#endif