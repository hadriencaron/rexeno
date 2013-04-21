#ifndef SHAPE_HH_
# define SHAPE_HH_

# include <string>
# include <iostream>
# include <string>
# include <boost/lexical_cast.hpp>
# include <map>

# include "parser.hh"
# include "variable.hh"

using namespace configuration;
using namespace std;

typedef map<int, bool> Status;


class Shape
{
public:
  Shape(const ShapeInfo& si,
        VariableManager& vm);
  Shape() {}
  virtual ~Shape() {}
  virtual void display();
  virtual void displayMonitor();
  virtual void react2input(Status&) = 0;
  const string& name() {return _name;}
  double frameStart() {return _frameStart->value;}
  double frameEnd() {return _frameEnd->value;}
  bool monitorDisplayable();
  uint ttl() {return _ttl;}
  bool displayable(int frameId);

protected:
  double _demiVertical(); // inside sub square-screen
  double _demiHorizontal(); // inside sub square-screen
  double _xGL(); // inside sub square-screen
  double _yGL(); // inside sub square-screen

  string _name;
  Variable* _frameStart;
  Variable* _frameEnd;
  Variable* _x;
  Variable* _y;
  Variable* _width;
  Variable* _height;
  Variable* _R;
  Variable* _G;
  Variable* _B;
  uint _ttl;
};

#endif
