#define BOOST_TEST_MODULE sessionTest
#include <boost/test/unit_test.hpp>

#include "parser.hh"

BOOST_AUTO_TEST_CASE( my_test )
{
  configuration::SessionInfo conf;
  bool r = configuration::CreateConfiguration("./conf", conf);

  BOOST_CHECK( r );
}

BOOST_AUTO_TEST_CASE( my_test_2 )
{
  //my_class test_object( "qwerty" );

  BOOST_CHECK( true );
}

