#ifndef WINDOW_HH_
# define WINDOW_HH_

# include "shape.hh"

class Window : public Shape
{
public:
  Window(const ShapeInfo&,
         VariableManager&,
         Trial* father);
  virtual ~Window() {}

  void Display();
  void DisplayMonitor();
  bool isIn(double x,
            double y);
  void React2input(Status&,
                   const datas&,
                   int,
                   ms);
  void Reset();
protected:
  double _thickness;
  Variable* _validationNbFrame;
  int _startValidationFrame;
  int _type;
  int _outsideValue;
};

class CorrectWindow : public Window
{
public:
  CorrectWindow(const ShapeInfo&,
                VariableManager&,
                Trial* father);
  ~CorrectWindow() {}
};

class WrongWindow : public Window
{
public:
  WrongWindow(const ShapeInfo&,
                VariableManager&,
                Trial* father);
  ~WrongWindow() {}
};

class FixationWindow : public Window
{
public:
  FixationWindow(const ShapeInfo&,
                VariableManager&,
                Trial* father);
  ~FixationWindow() {}
};

class NeutralWindow : public Window
{
public:
  NeutralWindow(const ShapeInfo&,
                VariableManager&,
                Trial* father);
  ~NeutralWindow() {}
};

#endif
