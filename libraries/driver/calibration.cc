#include "calibration.hh"
#include "setup.hh"

KeyboardCalibration::KeyboardCalibration()
{
  _m = new Matrix<double>(string("0 0"));

}

void
KeyboardCalibration::adjustPoint(datas& in)
{
  channel::iterator Xs;
  channel::iterator Ys;

  // in[0][0].volt = (*_m)(0);
  // in[1][0].volt = (*_m)(1);
  for (Xs = in[0].begin(); Xs != in[0].end(); ++Xs)
    Xs->volt = (*_m)(0);
  for (Ys = in[1].begin(); Ys != in[1].end(); ++Ys)
    Ys->volt = (*_m)(1);
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
}
