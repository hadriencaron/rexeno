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

  void Reset();

  bool getLead() { return *_lead;}
  double z() { return _z->value; }

  string getAttrsToString();


protected:
  float _angleX;
  float _angleY;
  float _angleZ;

  float _initX;
  float _initY;
  float _initZ;

  Variable* _lead;
  Variable* _slices;
  Variable* _stacks;
  Variable* _radius;

  Variable* _veloX;
  Variable* _veloY;
  Variable* _veloZ;

  Variable* _z;
  Variable* _dir;
  SphereShadow* _shadow;

  /****/

  time_t _lastime;
};


#endif
