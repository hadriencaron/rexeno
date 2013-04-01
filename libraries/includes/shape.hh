#ifndef SHAPE_HH_
# define SHAPE_HH_

# include <string>
# include <iostream>
# include <string>
# include "parser.hh"


using namespace configuration;
using namespace std;

class Shape
{
public:
  Shape(const ShapeInfo &si);
  ~Shape();

  virtual void display() = 0;
  virtual void react2input() = 0;
};

#endif
