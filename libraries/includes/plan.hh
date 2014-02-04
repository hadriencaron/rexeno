#ifndef PLAN_HH_
# define PLAN_HH_

# include <GL/glut.h>

# include "rectangle.hh"

class Plan : public Rectangle
{
	public:
		Plan(const ShapeInfo& si,
		         VariableManager& vm,
		         Trial* t);
		~Plan();

		void Display();
		string getAttrsToString();
	public:
		Variable* _repeat; // texture
};


#endif
