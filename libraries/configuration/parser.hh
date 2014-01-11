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
    std::string x_channel;
    std::string y_channel;
    std::string coordinates;
    std::string inputMethod;
    std::vector<TrialInfo> trials;
  };

  bool	CreateConfiguration(char const* filename,
			    SessionInfo &res);
}



#endif /* PARSER_HH_ */
