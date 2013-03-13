#include <iostream>
#include "parser.hh"
#include "session.hh"
#include <sys/types.h>
#include <signal.h>

int launch();

using namespace std;

int	main(int argc,
	     char **argv)
{
  configuration::sessionInfo conf;
  bool r = configuration::createConfiguration(argv[1], conf);

  int pid = fork();
  if (pid == 0)
    {
      while (1)
	{
	  printf("i am the child\n");
	  sleep(1);
	}
    }
  else
    {
      printf("i am the parent !\n");
      sleep(5);
      kill(pid, 9);
      launch();
    }
  Session s(conf);
}

