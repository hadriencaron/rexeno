#include <rexeno/interface/countermanding.hh>
#include <time.h>
#include <rexeno/PipeWriter/PipeWriter.hh>

int     tableau [5] ={1,4,7,10};// {2, 5, 8 ,12};//pour les PA
int     tableau2[5] = {4, 8, 12, 16};//pour les AP


void		PRO_Target1(TrialManager	*TM)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_TARGET1", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_TARGET1", "End_Fixation");
  Variable	*end_target = TM->GetVariable("PRO_TARGET1", "End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  end_target->value = end_fixation->value + 42;
}

void		PRO_Target2(TrialManager	*TM)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_TARGET2", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_TARGET2", "End_Fixation");
  Variable	*end_target = TM->GetVariable("PRO_TARGET2", "End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value =  fixation_duration->value;
  end_target->value = end_fixation->value + 42;
}

void		ANTI_Target1(TrialManager	*TM)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_TARGET1", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_TARGET1", "End_Fixation");
  Variable	*end_target = TM->GetVariable("ANTI_TARGET1", "End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  end_target->value = end_fixation->value + 42;
}

void		ANTI_Target2(TrialManager	*TM)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_TARGET2", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_TARGET2", "End_Fixation");
  Variable	*end_target = TM->GetVariable("ANTI_TARGET2", "End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value =  fixation_duration->value;
  end_target->value = end_fixation->value + 42;
}




// #define	IS_REDO		2
// #define IS_CORRECT	1
// #define IS_KO		(-1)

void	       ANTI_PRO_TARGET1_SSD1(TrialManager	*TM,
				int		r)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET1_SSD1", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET1_SSD1", "End_Fixation");
  Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET1_SSD1", "Start_Change");
  Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET1_SSD1", "End_Target");
 

int SSD1_TARGET_1_SSD1=tableau2[0];


  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD1_TARGET_1_SSD1;
  end_target->value = end_fixation->value + 42;
}

void	       ANTI_PRO_TARGET1_SSD2(TrialManager	*TM,
				int		r)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET1_SSD2", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET1_SSD2", "End_Fixation");
  Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET1_SSD2", "Start_Change");
  Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET1_SSD2", "End_Target");
 

int SSD1_TARGET_1_SSD2=tableau2[1];


  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD1_TARGET_1_SSD2;
  end_target->value = end_fixation->value + 42;
}

void	       ANTI_PRO_TARGET1_SSD3(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET1_SSD3", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET1_SSD3", "End_Fixation");
  Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET1_SSD3", "Start_Change");
  Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET1_SSD3", "End_Target");
 

  int SSD1_TARGET_1_SSD3=tableau2[2];


  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD1_TARGET_1_SSD3;
  end_target->value = end_fixation->value + 42;
}

void	       ANTI_PRO_TARGET1_SSD4(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET1_SSD4", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET1_SSD4", "End_Fixation");
  Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET1_SSD4", "Start_Change");
  Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET1_SSD4", "End_Target");
 

  int SSD1_TARGET_1_SSD4=tableau2[3];


  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD1_TARGET_1_SSD4;
  end_target->value = end_fixation->value + 42;
}

//  void	       ANTI_PRO_TARGET1_SSD5(TrialManager	*TM,
// 				     int		r)
// {
//   Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET1_SSD5", "Fixation_Duration");
//   Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET1_SSD5", "End_Fixation");
//   Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET1_SSD5", "Start_Change");
//   Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET1_SSD5", "End_Target");
 

//   int SSD1_TARGET_1_SSD5=tableau2[4];


//   fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
//   end_fixation->value = fixation_duration->value;
//   start_change->value = end_fixation->value + SSD1_TARGET_1_SSD5;
//   end_target->value = end_fixation->value + 42;
// }

void	       ANTI_PRO_TARGET2_SSD1(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET2_SSD1", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET2_SSD1", "End_Fixation");
  Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET2_SSD1", "Start_Change");
  Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET2_SSD1", "End_Target");

  int SSD1_TARGET_2_SSD1 = tableau2[0];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD1_TARGET_2_SSD1;
  end_target->value = end_fixation->value + 42;
}


void	       ANTI_PRO_TARGET2_SSD2(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET2_SSD2", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET2_SSD2", "End_Fixation");
  Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET2_SSD2", "Start_Change");
  Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET2_SSD2", "End_Target");

int SSD1_TARGET_2_SSD2 = tableau2[1];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD1_TARGET_2_SSD2;
  end_target->value = end_fixation->value + 42;
}

void	       ANTI_PRO_TARGET2_SSD3(TrialManager	*TM,
				int		r)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET2_SSD3", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET2_SSD3", "End_Fixation");
  Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET2_SSD3", "Start_Change");
  Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET2_SSD3", "End_Target");

int SSD1_TARGET_2_SSD3 = tableau2[2];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD1_TARGET_2_SSD3;
  end_target->value = end_fixation->value + 42;
}

void	       ANTI_PRO_TARGET2_SSD4(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET2_SSD4", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET2_SSD4", "End_Fixation");
  Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET2_SSD4", "Start_Change");
  Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET2_SSD4", "End_Target");

int SSD1_TARGET_2_SSD4 = tableau2[3];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD1_TARGET_2_SSD4;
  end_target->value = end_fixation->value + 42;
}

// void	       ANTI_PRO_TARGET2_SSD5(TrialManager	*TM,
// 				     int		r)
// {
//   Variable	*fixation_duration = TM->GetVariable("ANTI_PRO_TARGET2_SSD5", "Fixation_Duration");
//   Variable	*end_fixation = TM->GetVariable("ANTI_PRO_TARGET2_SSD5", "End_Fixation");
//   Variable	*start_change = TM->GetVariable("ANTI_PRO_TARGET2_SSD5", "Start_Change");
//   Variable	*end_target = TM->GetVariable("ANTI_PRO_TARGET2_SSD5", "End_Target");

// int SSD1_TARGET_2_SSD5 = tableau2[4];

//   fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
//   end_fixation->value = fixation_duration->value;
//   start_change->value = end_fixation->value + SSD1_TARGET_2_SSD5;
//   end_target->value = end_fixation->value + 42;
// }



void	       PRO_ANTI_TARGET1_SSD1(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET1_SSD1", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET1_SSD1", "End_Fixation");
  Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET1_SSD1", "Start_Change");
  Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET1_SSD1", "End_Target");
 
  int SSD_TARGET_1_SSD1 = tableau[0];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD_TARGET_1_SSD1;
  end_target->value = end_fixation->value + 42;
}

void	       PRO_ANTI_TARGET1_SSD2(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET1_SSD2", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET1_SSD2", "End_Fixation");
  Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET1_SSD2", "Start_Change");
  Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET1_SSD2", "End_Target");
 
  int SSD_TARGET_1_SSD2 = tableau[1];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60 
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD_TARGET_1_SSD2;
  end_target->value = end_fixation->value + 42;
}


void	       PRO_ANTI_TARGET1_SSD3(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET1_SSD3", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET1_SSD3", "End_Fixation");
  Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET1_SSD3", "Start_Change");
  Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET1_SSD3", "End_Target");
 
  int SSD_TARGET_1_SSD3 = tableau[2];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD_TARGET_1_SSD3;
  end_target->value = end_fixation->value + 42;
}


void	       PRO_ANTI_TARGET1_SSD4(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET1_SSD4", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET1_SSD4", "End_Fixation");
  Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET1_SSD4", "Start_Change");
  Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET1_SSD4", "End_Target");
 
  int SSD_TARGET_1_SSD4 = tableau[3];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD_TARGET_1_SSD4;
  end_target->value = end_fixation->value + 42;
}


// void	       PRO_ANTI_TARGET1_SSD5(TrialManager	*TM,
// 				     int		r)
// {
//   Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET1_SSD5", "Fixation_Duration");
//   Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET1_SSD5", "End_Fixation");
//   Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET1_SSD5", "Start_Change");
//   Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET1_SSD5", "End_Target");
 
//   int SSD_TARGET_1_SSD5 = tableau[4];

//   fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
//   end_fixation->value = fixation_duration->value;
//   start_change->value = end_fixation->value + SSD_TARGET_1_SSD5;
//   end_target->value = end_fixation->value + 42;
// }


void	       PRO_ANTI_TARGET2_SSD1(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET2_SSD1", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET2_SSD1", "End_Fixation");
  Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET2_SSD1", "Start_Change");
  Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET2_SSD1", "End_Target");
 
int SSD_TARGET_2_SSD1 = tableau[0];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD_TARGET_2_SSD1;
  end_target->value = end_fixation->value + 42;
}

 void	       PRO_ANTI_TARGET2_SSD2(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET2_SSD2", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET2_SSD2", "End_Fixation");
  Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET2_SSD2", "Start_Change");
  Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET2_SSD2", "End_Target");
 
  int SSD_TARGET_2_SSD2 = tableau[1];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD_TARGET_2_SSD2;
  end_target->value = end_fixation->value + 42;
}

void	       PRO_ANTI_TARGET2_SSD3(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET2_SSD3", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET2_SSD3", "End_Fixation");
  Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET2_SSD3", "Start_Change");
  Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET2_SSD3", "End_Target");
 
int SSD_TARGET_2_SSD3 = tableau[2];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD_TARGET_2_SSD3;
  end_target->value = end_fixation->value + 42;
}

void	       PRO_ANTI_TARGET2_SSD4(TrialManager	*TM,
				     int		r)
{
  Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET2_SSD4", "Fixation_Duration");
  Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET2_SSD4", "End_Fixation");
  Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET2_SSD4", "Start_Change");
  Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET2_SSD4", "End_Target");
 
  int SSD_TARGET_2_SSD4 = tableau[3];

  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value = fixation_duration->value;
  start_change->value = end_fixation->value + SSD_TARGET_2_SSD4;
  end_target->value = end_fixation->value + 42;
}

// void	       PRO_ANTI_TARGET2_SSD5(TrialManager	*TM,
// 				     int		r)
// {
//   Variable	*fixation_duration = TM->GetVariable("PRO_ANTI_TARGET2_SSD5", "Fixation_Duration");
//   Variable	*end_fixation = TM->GetVariable("PRO_ANTI_TARGET2_SSD5", "End_Fixation");
//   Variable	*start_change = TM->GetVariable("PRO_ANTI_TARGET2_SSD5", "Start_Change");
//   Variable	*end_target = TM->GetVariable("PRO_ANTI_TARGET2_SSD5", "End_Target");
 
//   int SSD_TARGET_2_SSD5 = tableau[4];

//   fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
//   end_fixation->value = fixation_duration->value;
//   start_change->value = end_fixation->value + SSD_TARGET_2_SSD5;
//   end_target->value = end_fixation->value + 42;
// }



//PipeWriter *pulse_pipe_analog = new PipeWriter(OUTPUT_ANALOGY_PIPE ,P_NORMAL);
PipeWriter *pulse_pipe_analog = new PipeWriter(5 ,P_NORMAL);
analogyMsg *t_pulseMsg = new analogyMsg;
int SendPulse()
{	
  // ICI je cré un pipe !

  // ICI j'écris dans le pipe
  t_pulseMsg->delay = 200000000; // == 150 msec
  t_pulseMsg->voltageValue = 5;
  t_pulseMsg->voltageValue = 10;
  pulse_pipe_analog->Write(t_pulseMsg,sizeof (analogyMsg));
}


void		InterTrial_CTM(TrialManager	*TM,
			       int		r) // Sera executée à chaque intertrial !
{
 Variable	*time = TM->GetVariable("INTERTRIAL", "TIME");
  if (r == -1)
    time->value = 30;
  else
    time->value = 30;

  if (r == 1)
    {
      SendPulse();
    }

  //PRO_Target1(TM);
  PRO_Target2(TM);

  ANTI_Target1(TM);
  ANTI_Target2(TM);

  ANTI_PRO_TARGET1_SSD1(TM,r);
  ANTI_PRO_TARGET1_SSD2(TM,r);
   ANTI_PRO_TARGET1_SSD3(TM,r);
  ANTI_PRO_TARGET1_SSD4(TM,r);
  //ANTI_PRO_TARGET1_SSD5(TM,r);

  ANTI_PRO_TARGET2_SSD1(TM,r);
   ANTI_PRO_TARGET2_SSD2(TM,r);
   ANTI_PRO_TARGET2_SSD3(TM,r);
  ANTI_PRO_TARGET2_SSD4(TM,r);
  //ANTI_PRO_TARGET2_SSD5(TM,r);

   PRO_ANTI_TARGET1_SSD1(TM,r);
   PRO_ANTI_TARGET1_SSD2(TM,r);
   PRO_ANTI_TARGET1_SSD3(TM,r);
  PRO_ANTI_TARGET1_SSD4(TM,r);
  //PRO_ANTI_TARGET1_SSD5(TM,r);

   PRO_ANTI_TARGET2_SSD1(TM,r);
   PRO_ANTI_TARGET2_SSD2(TM,r);
  PRO_ANTI_TARGET2_SSD3(TM,r);
   PRO_ANTI_TARGET2_SSD4(TM,r);
   //PRO_ANTI_TARGET2_SSD5(TM,r);
}

int main (int argc, char **argv)
{
  mlockall(MCL_CURRENT|MCL_FUTURE);

  srand ( time(NULL) );
  vector<vect*>		*data;
  vector<vect*>::iterator		it;
  XenoTimer	*xtimer = new XenoTimer();
  CounterManding *interface = new CounterManding ();

  interface->time_intertrial = 30;
  Displayer::frame_mode = 1;

  // Set Background here :
  interface->R = 0.3;
  interface->B = 0.3;
  interface->G = 0.3;

  interface->InterTrial = NULL;
  interface->InterTrial = &InterTrial_CTM;


  interface->CreateDisplays ("conf");
  interface->GenerateTrials ("ctm");
  interface->BuildInterface (argc, argv); // Used to be 2nd window;
  interface->EndInterface ();

}
