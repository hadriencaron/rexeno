#ifndef SPHERE_HH_
# define SPHERE_HH_

# include "shape.hh"
# include "sphereshadow.hh"

#include <GL/glut.h>
class Sphere : public Shape
{
public:
   Sphere(const ShapeInfo& si,
         VariableManager& vm,
         Trial* father);
  ~Sphere();

  void React2input(Status&,
                   const datas&,
                   int,
                   ms);

  void Display();
  void DisplayMonitor();

  void setIsWorking(bool b) { _isWorking = b; }
  void Reset();

  bool getLead() { return *_lead;}
  bool getIsWorking() { return _isWorking; }
  float getX() { return *_x;}

  string getAttrsToString();


protected:
  float _angleX;
  float _angleY;
  float _angleZ;
  bool _isWorking;

  Variable* _lead;
  Variable* _slices;
  Variable* _stacks;
  Variable* _radius;

  Variable* _veloX;
  Variable* _veloY;
  Variable* _veloZ;

  Variable* _z;
  SphereShadow* _shadow;

  /****/

  time_t _lastime;
};


#endif
