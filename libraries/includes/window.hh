#ifndef WINDOW_HH_
# define WINDOW_HH_

# include "shape.hh"

class Window
{
public:
  Window(const ShapeInfo&,
         variableManager&,
         Trial* father);
  Window() {}
  virtual ~Window();

  void display();
  void displayMonitor();
  bool isIn(double x,
            double y);
private:
  double _thickness;
};


#endif
