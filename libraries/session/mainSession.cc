#include <iostream>
#include <GL/glut.h>

#include "session.hh"
#include "dummyDriver.hh"

using namespace std;


void		GO_Target1(VariableManager& TM)
{
  // Variable	*fixation_duration = TM->GetVariable("GO_TARGET1", "Fixation_Duration");
  Variable	*fixation_duration = new Variable(0);
  Variable	*end_fixation = TM.getVariable("End_Fixation");
  Variable	*end_target = TM.getVariable("End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  end_target->value = end_fixation->value + 60;
}

void		GO_Target2(VariableManager& TM)
{
  // Variable	*fixation_duration = TM->GetVariable("GO_TARGET2", "Fixation_Duration");
  Variable	*fixation_duration = new Variable(0);
  Variable	*end_fixation = TM.getVariable("End_Fixation");
  Variable	*end_target = TM.getVariable("End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value =  fixation_duration->value;
  end_target->value = end_fixation->value + 60;
}


void		InterTrial_CTM(std::string &name,
                               VariableManager& TM)
			       //int r) // Sera executée à chaque intertrial !
{
  //std::cout << "REDO ? " << r << std::endl;
  // if (r == 1)
  //   {
  //     std::cout << "Send Pulse" << std::endl;
  //   }

 // GO_Target1(TM);
 // GO_Target2(TM);
  //Variable* start = TM.getVariable("Start_Correct");
  Variable* end = TM.getVariable("End_Target");
  //start->value = 1160;
  end->value = 1160;
}




int	main(int argc,
	     char **argv)
{
  configuration::SessionInfo conf;
  vector<int> t;
  cout << t.size() << endl;
  bool r = configuration::createConfiguration("../../protocoles/DevTests/conf", conf);
  bool r2 = configuration::createTrialOrder("../../protocoles/DevTests/ctm", t);
  assert(r && r2);
  Setup* setup = new Setup("~/.rexeno");
  Session* session = Session::GetInstance(conf,t);
  // Driver* d = new DummyDriver();

  session->setup = setup;
  session->beforeTrial = &InterTrial_CTM;

  session->run(argc, argv);
}
