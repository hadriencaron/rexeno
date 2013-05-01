#ifndef WINDOW_HH_
# define WINDOW_HH_

# include "shape.hh"

class Window : public Shape
{
public:
  Window(const ShapeInfo&,
         VariableManager&,
         Trial* father);
  Window() {}
  virtual ~Window() {}

  void display();
  void displayMonitor();
  bool isIn(double x,
            double y);
private:
  double _thickness;
  int _validationNbFrame;
};

class CorrectWindow : public Window
{
public:
  CorrectWindow(const ShapeInfo&,
                VariableManager&,
                Trial* father);
  CorrectWindow() {}
  ~CorrectWindow() {}

  void react2input(Status&,
                   datas& ds,
                   ms);

};

#endif
