#ifndef	TRIAL_HH_
# define TRIAL_HH_

# include <map>
# include <set>
# include <string>
# include "parser.hh"
# include "shape.hh"
# include "square.hh"
# include "cross.hh"
# include "session.hh"
# include "window.hh"
# include <GL/glut.h>

using namespace std;
using namespace configuration;
class Shape;
class Square;
class Driver;

# define RUNNING 0
# define PAUSE 1
# define WRONG_REDO 2
# define WRONG_NEXT 3
# define CORRECT 4
# define WAITING_FIXATION 5
# define NEUTRAL 6

struct TtlEvent
{
  TtlEvent() {delay=0;value=0;}
  double delay;
  uint value;
};

class Trial
{
public:
  Trial(TrialInfo& ti);
  ~Trial();
  int displayFrame(Driver* d);
  bool finished();
  bool atStart();
  string& name() {return _name;}
  void reset();
  void adjustNbFrames();
  void addTtl();
  bool status(int);
  int frameEnd() {return _nbFrames;}
  VariableManager variables;
private:
  int _react2status();
  void _sendTtls(Driver* d);

  int _curFrameId;
  int _nbFrames;
  Status _status;
  vector<Shape*> _shapes;
  string& _name;
  int _argc;
  char **_argv;
  vector<TtlEvent*>* _ttl;
  datas _data;
  bool _logged;
};


#endif
