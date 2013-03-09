#ifndef PARSER_HH_
# define PARSER_HH_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>



namespace configuration
{
  namespace qi = boost::spirit::qi;
  //namespace ascii = boost::spirit::ascii;
  namespace standard = boost::spirit::standard;

  ///////////////////////////////////////////////////////////////////////////
  //  Our moses struct
  ///////////////////////////////////////////////////////////////////////////
  struct shapeInfo
  {
    std::string name;
    std::vector<std::string> attributes;
  };

  struct trialInfo
  {
    int time;
    std::string name;
    std::vector<shapeInfo> shapes;
  };

  struct screenInfo
  {
    int	height;
    int	width;
  };

  struct sessionInfo
  {
    std::string name;
    std::string comment;

    int polarCoordonates; // Default No
    std::vector<screenInfo> screens; // Default Yes
    std::vector<trialInfo> trials;
  };

  bool	createConfiguration(char const* filename,
			    sessionInfo &res);

}



#endif /* PARSER_HH_ */
