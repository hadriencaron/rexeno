#ifndef SHAPE_HH_
# define SHAPE_HH_

# include <string>
# include <iostream>
# include <string>
# include <boost/lexical_cast.hpp>
# include <map>

# include "parser.hh"
# include "variable.hh"
# include "types.hh"

using namespace configuration;
using namespace std;

typedef map<int, bool> Status;



class Trial;




class Shape
{
public:
  Shape(const ShapeInfo& si,
        VariableManager& vm,
        Trial* father);
  Shape();
  virtual ~Shape() {}
  virtual void Display();
  virtual void DisplayMonitor();
  virtual void React2Input(Status&,
                           datas&,
                           int,
                           ms);
  double x() {return _x->value;}
  double y() {return _y->value;}
  const string& Name() {return _name;}
  double FrameStart() {return _frameStart->value;}
  double FrameEnd() {return _frameEnd->value;}
  bool MonitorDisplayable();
  uint Ttl() {return _ttl;}
  bool Displayable(int frameId);

protected:
  // Use these functions for opengl's drawing scale. 
  double _DemiVertical(); // inside sub square-screen
  double _DemiHorizontal(); // inside sub square-screen
  double _Xgl(); // inside sub square-screen
  double _Ygl(); // inside sub square-screen

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
  Trial* _father;
  bool _logged;
  bool _loggedEnd;
};

#endif
