#include "parser.hh"
#include "model.hh"
#include <iostream>
#include<fstream>

Model::Model()
{

}

void
Model::setTrialName(const string& trialName)
{
  _trialName = trialName;
}

void
Model::addShape2Trial(const string& shape)
{
  _availableShapes.push_back(shape);
}

void
Model::fillAvailableShapes(const string& confFile)
{
  string sLine;
  ifstream infile;
  infile.open (confFile.c_str());
  string previousLine="";

  while (!infile.eof())
  {
    getline(infile, sLine);
    cout << sLine << endl;
  }  
  infile.close();
}
