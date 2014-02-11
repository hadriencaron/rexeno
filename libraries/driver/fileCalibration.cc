#include "calibration.hh"
#include <iostream>

FileCalibration::~FileCalibration()
{
  delete _points;
}

void
FileCalibration::AddPoint(double	Th,
                          double	Obs)
{
  _points->push_back(pair<double,double>(Th,Obs));
}

#include <fstream>
#include <sstream>
void
FileCalibration::Save(string		filename)
{
  ofstream	Fichier (filename.c_str()); 
  
  if ( !Fichier)
    {
      return ;
    }
  
  for (unsigned int i = 0; i < _points->size(); ++i)
    {
      pair<double, double>	p = (*_points)[i];

      Fichier << p.first << " " << p.second << std::endl;
    }
}

FileCalibration::FileCalibration(string	filename)
{
  ifstream	Fichier(filename.c_str(), ifstream::in);
  _points = new vector<pair<double, double> >();
  _ready = false;

  assert(Fichier);
  if (!Fichier)
    {
      return ;
    }
  while (!Fichier.eof())
    {
      double	th, obs;

      Fichier >> th;
      Fichier >> obs;

      AddPoint(th, obs);
    }
  CalculateCalibration();
  _ready = true;
}

int
FileCalibration::NbPoints()
{
  return (_points->size());
}

bool
FileCalibration::IsReady()
{
  return(_ready);
}
