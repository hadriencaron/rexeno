#ifndef SESSION_HH_
# define SESSION_HH_

# include <iostream>
# include <list>

# include "parser.hh"
# include <GL/glut.h>

using namespace std;
using namespace configuration;
class Trial;

class Session
{
public:
  Session(SessionInfo	&s);
  ~Session();
  void	run();
private:
  vector<Trial*> _trials;
  SessionInfo& _info;
};


#endif

