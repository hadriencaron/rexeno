#define BOOST_TEST_MODULE sessionTest
#include <boost/test/unit_test.hpp>

#include "parser.hh"

BOOST_AUTO_TEST_CASE( my_test )
{
  configuration::SessionInfo conf;
  try
  {
    bool r = configuration::CreateConfiguration("../../../unitTest/testFiles/session/conf", conf);
    BOOST_CHECK( r );
  }
  catch(int e)
  {
    BOOST_CHECK( false );
  }
}

BOOST_AUTO_TEST_CASE( my_test_2 )
{
  //my_class test_object( "qwerty" );

  BOOST_CHECK( true );
}

