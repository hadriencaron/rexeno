
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
	assert(si.attributes.size() == 17);

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
	vm.addVariable(_dir = new Variable(si.attributes[16]));

	_angleX = 0.0f;
	_angleY = 0.0f;
	_angleZ = 0.0f;

	_initX = *_x;
	_initY = *_y;
	_initZ = *_z;

	_father = father;
	_lastime = 0;

	SphereShadow* s = new SphereShadow(*_radius, *_z, *_stacks, true);
	_shadow = s;

	if (*_dir == false){
		_randomDir = true;
		RandomDir();
	}
	else{
		_randomDir = false;
	}


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

	  Session* session = Session::getInstance();
	  // Saving of shape apparition
	//  std::cout << "FrameId => " << frameId << "frameStart => " << frameStart() << "Logged (false?) => " << _logged << endl;
	  if ((frameId == frameStart()) && (!_logged))
	  {
	    _logged = true;
		string s;
		ostringstream ostr;
		ostr << _name << " start " << lexical_cast<string>(displayTime) << " Pos [" << RoundNdecimal(2,_x->value) << ", " << RoundNdecimal(2,_y->value) << ", " << RoundNdecimal(2,_z->value) <<"]";
		s = ostr.str();
	//	printf("Logged passe a vrai\n");
	    session->recorder->Save(s, "events.txt");
	  }
	  // Saving of shape disparation
//	  std::cout << "FrameId => " << frameId << "frameEnd => " << frameEnd() << "LoggedEnd (false?) => " << _loggedEnd << endl;
	  if ((frameId == frameEnd()) && (!_loggedEnd))
	  {
		string s;
		ostringstream ostr;
		ostr << _name << " end " << lexical_cast<string>(displayTime) << " Pos [" << RoundNdecimal(2,_x->value) << ", " << RoundNdecimal(2,_y->value) << ", " << RoundNdecimal(2,_z->value) <<"]";
		s = ostr.str();
		session->recorder->Save(s, "events.txt");
	//	printf("LoggedEnd passe a vrai\n");
	    _loggedEnd = true;
	  }
	  std::cout << "Frame Id => " << frameId << " FrameEnd => " << frameEnd() << displayTime <<endl;
	  session->recorder->Save(_name + "\n" + lexical_cast<string>(_x->value) + "\n" + lexical_cast<string>(_y->value) + "\n" + lexical_cast<string>(displayTime), "square_targets.txt");

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
	/*	if (_lastime == 0){
			_lastime = glutGet(GLUT_ELAPSED_TIME);
		}

		time_t now = glutGet(GLUT_ELAPSED_TIME);
		const double FrameTime = difftime(now, _lastime);
*/
		if (this->IsTextured() == false){
			ImageLoad iload;
			iload.setFilename("/home/xeno1/workspace/TinDPe/src/textures/test.bmp");
			if(!(iload.load())){
				exit(1);
			}

			this->initTexture(iload.getSizeY(), iload.getSizeX(), iload.getData());
		}

		if (*_dir==1){
		//	if (*_x>(-0.8)){
				float move = *_veloX/60;
				float angleX = move / *_radius*180.0 / M_PI;

				_angleX = _angleX+angleX;
				std::cout << "X => " << *_x << endl;

				if (_angleX>360){
					double nb = 360.0- _angleX;
					_angleX=nb;
				}

				*_x = *_x-move;
		/*	}
			else{
				// *_x = -0.8f;
				*_x = _initX;
				*_y = _initY;
				*_z = _initZ;
			}*/
		}
		else if (*_dir==2){
		//	if (*_x<(0.8)){
				float move = *_veloX/60;
				float angleX = move / *_radius*180.0 / M_PI;

				_angleX = _angleX-angleX;
				std::cout << "X => " << *_x << endl;

				if (_angleX>360){
					double nb = 360.0- _angleX;
					std::cout << "NB => " << nb;
					_angleX=nb;
				}
				*_x = *_x+move;
		/*	}
			else{
				*_x = _initX;
				*_y = _initY;
				*_z = _initZ;
			}*/
		}

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

//		_lastime = now;
}

void
Sphere::Reset(){

	*_x = _initX;
	*_y = _initY;
	*_z = _initZ;

	_logged = false;
	_loggedEnd = false;
	//_lastime = 0;
	if (_randomDir == true){
		RandomDir();
	}
}

void
Sphere::RandomDir(){
	int dir = rand()%(3-1)+1;
	*_dir = dir;
}
void
Sphere::DisplayMonitor()
{

}

string
Sphere::getAttrsToString(){
	string s;
	float move = *_veloX/60;
	float angleX = (move / *_radius*180.0 / M_PI)*60;
	//angleX = floor(RoundNdecimal(2,angleX)*100.0)/100.0;
	move = *_veloY/60;
	float angleY = (move / *_radius*180.0 / M_PI)*60;
	move = *_veloZ/60;
	float angleZ = (move / *_radius*180.0 / M_PI)*60;
	ostringstream ostr;
	ostr <<  _name << ": Radius ["
			<< *_radius << "] Velocity [" << *_veloX << ", " << *_veloY <<", " << *_veloZ <<"] Angle ["
			<<RoundNdecimal(2,angleX)
			<<", "
			<<RoundNdecimal(2,angleY)
			<<", "
			<<RoundNdecimal(2,angleZ) <<"]";
	s = ostr.str();
	return s;
}

