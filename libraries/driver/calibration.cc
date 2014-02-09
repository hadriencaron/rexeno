#include "calibration.hh"
#include "setup.hh"
#include "matrix.hh"

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

KeyboardCalibration::~KeyboardCalibration()
{
  delete _m;
}

FileCalibration::FileCalibration(std::string filename)
{
  _filename = filename;
  _stream.open(filename.c_str());
  _matrix_calibration = new Matrix<double>("1 0 0 ; 0 1 0 ; 0 0 1");
  _vector_in = new Matrix<double>("1 ; 0 ; 0");
  _vector_out = new Matrix<double>("1 ; 0 ; 0");
}

FileCalibration::~FileCalibration()
{
  _stream.close();
}

void
FileCalibration::adjustPoint(datas& d)
{
  datas::iterator it;
  channel Xs = d[0];
  channel Ys = d[1];
    
  (*_vector_in)(0) = Xs[0].volt;
  (*_vector_in)(1) = Ys[0].volt;
  (*_vector_in)(1) = 1;
  for (it = d.begin(); it != d.end(); ++it)
  {
    _vector_out->Mult(*_matrix_calibration, *_vector_in);
  }
  Xs[0].volt = (*_vector_out)(0);
  Ys[0].volt = (*_vector_out)(1);
}

void
FileCalibration::React2input()
{

}
