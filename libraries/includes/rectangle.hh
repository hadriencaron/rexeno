#ifndef RECTANGLE_HH_
# define RECTANGLE_HH_

# include "shape.hh"

class Rectangle : public Shape
{
public:
  Rectangle(const ShapeInfo&,
            VariableManager&,
            Trial* father);
  Rectangle() {}
  virtual ~Rectangle();

  void react2input(Status&);
private:
};

#endif

