#ifndef MODEL_HH_
# define MODEL_HH_

using namespace std;
# include <vector>
# include "parser.hh"
# include <map>

class Model
{
public:
  Model();
  void setTrialName(const string&);
  void setShape(const string&);
  void addShape2Trial(const string&);

  string trialName() {return _trialName;}
  void fillAvailableShapes(const string& confFile);
  const vector<string>& availableShapes() {return _availableShapes;}
  vector<vector<string> > protocole;
  map<string, vector<string> > shapePrototypes;
private:
  string _trialName;
  vector<string> _availableShapes;
  configuration::ShapeInfo _newShape;
  configuration::TrialInfo _curTrial;
};


#endif /* MODEL_HH_ */
