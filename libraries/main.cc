#include <iostream>
#include "parser.hh"

using namespace std;

int	main(int argc,
	     char **argv)
{
  
  cout << "ceci est un test" << endl;
  configuration::sessionInfo conf;

  bool r = configuration::createConfiguration(argv[1], conf);

}

