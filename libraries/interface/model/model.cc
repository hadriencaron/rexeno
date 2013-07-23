#include "parser.hh"
//#include "interface.hh"
#include "model.hh"

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
