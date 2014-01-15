#ifndef PARSER_HH_
# define PARSER_HH_


#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>



namespace configuration
{

  ///////////////////////////////////////////////////////////////////////////
  //  Our moses struct
  ///////////////////////////////////////////////////////////////////////////
  struct ShapeInfo
  {
    std::string name;
    std::vector<std::string> attributes;
  };

  struct TrialInfo
  {
    int time;
    std::string name;
    std::vector<ShapeInfo> shapes;
  };


  struct SessionInfo
  {
    SessionInfo() {}
    ~SessionInfo() {}

    std::string name;
    int x_channel;
    int y_channel;
    std::string coordinates_type;
    std::string driver;
    std::string calibration_type;
    bool enable_replay;
    std::vector<TrialInfo> trials;
  };

  bool	CreateConfiguration(char const* filename,
			    SessionInfo &res);
}



#endif /* PARSER_HH_ */
