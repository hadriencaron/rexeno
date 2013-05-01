#ifndef CROSS_HH_
# define CROSS_HH_

# include "shape.hh"

class Cross : public Shape
{
public:
  Cross(const ShapeInfo&,
        VariableManager&,
        Trial* father);
  Cross() {}
  ~Cross() {}

  void display();
  void displayMonitor();
  void react2input(Status&,
                   datas&,
                   ms frameId);
};

#endif
