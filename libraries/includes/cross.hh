#ifndef CROSS_HH_
# define CROSS_HH_

class Cross : public Shape
{
  Cross();

  void display(const ShapeInfo&,
               VariableManager&);
  void displayMonitor();
}
  
#endif CROSS_HH_

