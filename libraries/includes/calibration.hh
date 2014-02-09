#ifndef CALIBRATION_HH_
# define CALIBRATION_HH_

# include "matrix.hh"
# include "types.hh"
# include "iostream"
# include "fstream"

class Calibration
{
public:
  Calibration() {}
  virtual ~Calibration() {}

  virtual void adjustPoint(datas&) = 0;
  virtual void React2input() = 0;
};

class KeyboardCalibration : public Calibration
{
public:
  KeyboardCalibration();
  ~KeyboardCalibration();

  void adjustPoint(datas&);
  void React2input();
private:
  Matrix<double>* _m;
};

class FileCalibration : public Calibration
{
public:
  FileCalibration(std::string f);
  ~FileCalibration();
  void adjustPoint(datas&);
  void React2input();
private:
  Matrix<double>* _m;
  std::string _filename;
  std::ifstream _stream;
  Matrix<double>* _matrix_calibration;
  Matrix<double>* _vector_in;
  Matrix<double>* _vector_out;
};

#endif
