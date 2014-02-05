/**
 * @file   shape.hh
 * @author hadrien <hadrien@barbow>
 * @date   Tue May 21 22:45:52 2013
 * 
 * @brief  
 * 
 * Defines the Shape class
 * Shape is a purely abstract that designates the elements that can appear during a trial.
 * Most of the time, a shape has a color and dimensions (for example a Circle or a Square)
 * but it is possible to create objects that only affect the outcome of the trial without
 * anything being displayed directly (kind of the case of Window)
 */

#ifndef SHAPE_HH_
# define SHAPE_HH_

# include <GL/glut.h>

# include <string>
# include <iostream>
# include <string>
# include <boost/lexical_cast.hpp>
# include <map>
# include <assert.h>

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
  virtual void React2input(Status&,
                           const datas&,
                           int,
                           ms);
  virtual void initTexture(int sizeX, int sizeY, char * data);
  double x() {return _x->value;}
  double y() {return _y->value;}
  virtual double z() { return 0.0; }
  int id() {return _id;}
  const string& name() {return _name;}
  double frameStart() {return _frameStart->value;}
  double frameEnd() {return _frameEnd->value;}
  bool MonitorDisplayable();
  uint ttl() {return _ttl;}
  bool Displayable(int frameId);
  bool SubjectVisible(){return _subjectVisible;}
  virtual void Reset();
  virtual bool getIsWorking(){ return false;}
  virtual string getAttrsToString();


  bool IsTextured(){ return _istexured;}

protected:
  // Use these functions for opengl's drawing scale. 
  double _demiVertical(); // inside sub square-screen
  double _demiHorizontal(); // inside sub square-screen
  double _xGL(); // inside sub square-screen
  double _yGL(); // inside sub square-screen

  int _id;

  GLuint _texture[1];
  GLUquadric* _params;

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
  bool _subjectVisible;
  bool _istexured;
};

#endif
