#include "parser.hh"
#include "model.hh"
#include <iostream>
#include<fstream>

#include <boost/algorithm/string.hpp>

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
  std::vector<std::string> strs;

  while (!infile.eof())
  {
    getline(infile, sLine);
    boost::split(strs, "string to split", boost::is_any_of("\t "));
    _availableShapes.push_back(strs[0]);
    cout << strs[0] << endl;
  }  
  infile.close();
}
