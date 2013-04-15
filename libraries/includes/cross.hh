#ifndef CROSS_HH_
# define CROSS_HH_

# include "shape.hh"

class Cross : public Shape
{
  Cross(const ShapeInfo&,
        VariableManager&);

  void display();
  void displayMonitor();
  void react2input(Status&);
};

#endif
