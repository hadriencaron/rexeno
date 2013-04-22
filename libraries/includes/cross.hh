#ifndef CROSS_HH_
# define CROSS_HH_

# include "shape.hh"

class Cross : public Shape
{
public:
  Cross(const ShapeInfo&,
        VariableManager&);
  Cross() {}
  ~Cross() {}

  void display();
  void displayMonitor();
  void react2input(Status&);
};

#endif
