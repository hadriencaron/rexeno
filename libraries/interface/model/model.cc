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
  std::vector<std::string>::iterator it;
 
  while (!infile.eof())
  {
    getline(infile, sLine);
    boost::split(strs, sLine, boost::is_any_of("\t "));
    _availableShapes.push_back(strs[0]);
    cout << strs[0] << endl;
    vector<string>::const_iterator first = strs.begin() + 1;
    vector<string>::const_iterator last = strs.end();
    shapePrototypes[strs[0]] = vector<string>(first, last);
  }  
  infile.close();
  for (it = strs.begin(); it != strs.end(); ++it)
  {
    

  }
}
