#ifndef MODEL_HH_
# define MODEL_HH_

using namespace std;
# include <vector>
# include "parser.hh"

class Model
{
public:
  Model();
  void setTrialName(const string&);
  void setShape(const string&);
  void addShape2Trial(const string&);

  string trialName() {return _trialName;}
private:
  string _trialName;
  vector<string> _availableShapes;
  configuration::ShapeInfo _newShape;
  configuration::TrialInfo _curTrial;
};


#endif /* MODEL_HH_ */
