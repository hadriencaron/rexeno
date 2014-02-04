
#include <math.h>
#include "sphere.hh"
#include "imageload.hh"
#include <GL/glut.h>
#include <trial.hh>

#include "recorder.hh"
#include "setup.hh"

using boost::lexical_cast;
using boost::bad_lexical_cast;
class Trial;

Sphere::Sphere(const ShapeInfo& si,
		VariableManager& vm,
		Trial* father)
{
	assert(si.attributes.size() == 16);

	_name = si.attributes[0];
	_id = 7;

	vm.addVariable(_x = new Variable(si.attributes[1]));
	vm.addVariable(_y = new Variable(si.attributes[2]));
	vm.addVariable(_z = new Variable(si.attributes[3]));
	vm.addVariable(_frameStart = new Variable(si.attributes[4]));
	vm.addVariable(_frameEnd = new Variable(si.attributes[5]));
	vm.addVariable(_R = new Variable(si.attributes[6]));
	vm.addVariable(_G = new Variable(si.attributes[7]));
	vm.addVariable(_B = new Variable(si.attributes[8]));
	vm.addVariable(_stacks = new Variable(si.attributes[9]));
	vm.addVariable(_slices = new Variable(si.attributes[10]));
	vm.addVariable(_radius = new Variable(si.attributes[11]));
	vm.addVariable(_veloX = new Variable(si.attributes[12]));
	vm.addVariable(_veloY = new Variable(si.attributes[13]));
	vm.addVariable(_veloZ = new Variable(si.attributes[14]));
	vm.addVariable(_lead = new Variable(si.attributes[15]));

	_angleX = 0.0f;
	_angleY = 0.0f;
	_angleZ = 0.0f;
	_father = father;
	_lastime = 0;
	_isWorking = false;

	SphereShadow* s;
	s = new SphereShadow(*_radius, *_z, *_stacks, true);
	_shadow = s;

}

Sphere::~Sphere()
{
	delete _shadow;
}

void
Sphere::React2input(Status& s,
		const datas& ds,
		int frameId,
		ms displayTime)
{
	  if (ds[0][0].rep != (-1)){
		  printf("J'ai une réponse! => %d \n", ds[0][0].rep);
		  s[CORRECT] = true;
	  }
	  Session* session = Session::getInstance();
	  // Saving of shape apparition

	  if ((frameId == frameStart()) && (!_logged))
	  {
	    _logged = true;
		string s;
		ostringstream ostr;
		ostr << _name << " start " << lexical_cast<string>(displayTime) << " Pos [" << *_x << ", " << *_y << ", " << *_z <<"]";
		s = ostr.str();
	    session->recorder->Save(s, "events.txt");
	  }
	  // Saving of shape disparation
	  if ((frameId == frameEnd()) && (!_loggedEnd))
	  {
		string s;
		ostringstream ostr;
		ostr << _name << " end " << lexical_cast<string>(displayTime) << " Pos [" << *_x << ", " << *_y << ", " << *_z <<"]";
		s = ostr.str();
		session->recorder->Save(s, "events.txt");
	    _loggedEnd = true;
	  }

	  session->recorder->Save(_name + "\n" + lexical_cast<string>(this->_x->value) + "\n" + lexical_cast<string>(this->_y->value) + "\n" + lexical_cast<string>(displayTime), "square_targets.txt");

	  if (frameId > frameEnd())
	    s[RUNNING] |= false;
	  else
	    s[RUNNING] = true;

	  session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " display", "logger.txt");
//	Shape::React2input(s, ds, frameId, displayTime);
}

void
Sphere::Display()
{
		if (_lastime == 0){
			_lastime = glutGet(GLUT_ELAPSED_TIME);
		}

		time_t now = glutGet(GLUT_ELAPSED_TIME);
		const double FrameTime = difftime(now, _lastime);

		if (this->IsTextured() == false){
			ImageLoad iload;
			std::cout << "Texture => " << this->IsTextured() << endl;
			iload.setFilename("/home/xeno1/workspace/TinDPe/src/textures/test.bmp");
			if(!(iload.load())){
				exit(1);
			}

			this->initTexture(iload.getSizeY(), iload.getSizeX(), iload.getData());
		}

		if (*_x>(-0.8)){
			float move = *_veloX*FrameTime/1000.0;
			float angleX = move / *_radius*180.0/M_PI;
			_isWorking = true;

			glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);

			int spec[4] = {1,1,0,1};
			int light[4] = {0,0,4,0};

			//if (shadow.getActive()==1){
			glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
			glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 2);
			glLightiv(GL_LIGHT0, GL_POSITION, light);
			//}

			_params = gluNewQuadric();

			glEnable( GL_TEXTURE_2D );
			glBindTexture(GL_TEXTURE_2D, _texture[0]);

			gluQuadricDrawStyle(_params,GLU_FILL);

			///  if (_x==0){
			_angleX = _angleX+angleX;
			//printf("Angle => %f\n ", angleX);

			if (_angleX>360){
				double nb = 360.0- _angleX;
				_angleX=nb;
			}

			*_x = *_x-move;

			/*    }
			else if (this->dir==1){
				this->angle = this->angle-angle;
				if (this->angle<1){
				this->angle=360;

				}
				this->move = this->move+move;
				if (this->move>(2)){
					this->move = 0.0f;
				}
			}*/

			glTranslated(*_x,*_radius+*_y,*_z);
			glRotated(_angleX,0,0,1);
			glRotated(90.0f,1,0,0);

			gluQuadricTexture(_params ,GL_TRUE);
			gluSphere(_params, *_radius, *_stacks, *_slices);
			gluDeleteQuadric(_params);

			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable( GL_TEXTURE_2D );
			_shadow->setPos(*_x, *_y, *_z);
			_shadow->Display();
		}
		else{
			*_x = -0.8f;
			_isWorking = false;
		}

		_lastime = now;
}

void
Sphere::Reset(){
	*_x = 0.8;
}

void
Sphere::DisplayMonitor()
{

}

string
Sphere::getAttrsToString(){
	string s;
	ostringstream ostr;
	ostr <<  _name << ": Radius ["<<*_radius <<"] Velocity ["<<*_veloX <<", "<<*_veloY <<", "<<*_veloZ <<"] Angle ["<<_angleX <<", "<<_angleY <<", "<<_angleZ <<"]";
	s = ostr.str();
	return s;
}

