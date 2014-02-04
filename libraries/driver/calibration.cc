#include "calibration.hh"
#include "setup.hh"

KeyboardCalibration::KeyboardCalibration()
{
  _m = new Matrix<double>(string("0 0"));
  _rep = -1;
}

void
KeyboardCalibration::adjustPoint(datas& in)
{
  datas::iterator it;

  in[0][0].volt = (*_m)(0);
  in[1][0].volt = (*_m)(1);

  in[0][0].rep = _rep;
//  std::cout << "Rep => " << in[0][0].rep << std::endl;

  // for (it = in.begin(); it != in.end(); ++it)
  // {
  //   (*it)[0].volt = (*_m)(0);
  //   (*it)[1].volt = (*_m)(1);
  // }
}

void
KeyboardCalibration::React2input()
{
  if (Setup::keys['q'])
    (*_m)(0) -= 0.025;
  if (Setup::keys['d'])
    (*_m)(0) += 0.025;
  if (Setup::keys['z'])
    (*_m)(1) -= 0.025;
  if (Setup::keys['s'])
    (*_m)(1) += 0.025;
  if (Setup::keys['a'])
	_rep = 1;
  if (Setup::keys['b'])
	_rep = 2;
}
void
KeyboardCalibration::Reset(){
	_rep = -1;
}
