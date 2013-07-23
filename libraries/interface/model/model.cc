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
  ifstream myReadFile;
  myReadFile.open(confFile.c_str());
  string output;
  if (myReadFile.is_open())
  {
    while (!myReadFile.eof())
    {
      myReadFile >> output;
      cout<<output;
    }
  }
  myReadFile.close();
}
