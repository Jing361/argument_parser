#include<iostream>
#include<string>
#include<exception>

#define CATCH_CONFIG_MAIN
#include<catch/catch.hpp>

#include<argparse.hh>

using namespace std;

TEST_CASE( "Arguments can be checked by existence", "[parser]" ){
  argparse ap;
  const char* argw[] = { "main", 
                         "--test", "a",
                         "--aoeu", "1",
                         "--htns", "abc", "xyz",
                         "--str", "test",
                         "-test", "b" };
  int argd = 12;

  ap.add_argument( "--test", "", 1 );
  ap.add_argument( "--aoeu", "", 1 );
  ap.add_argument( "--htns", "", 2 );
  ap.add_argument( "--str", "", 1 );
  ap.add_argument( "--default", "12", 1 );
  ap.add_argument( "-test" );
  ap.add_argument( "none" );

  SECTION( "Catches unspecified arguments" ){
    bool unspecifiedSanity = false;

    try{
      ap.parse_args( argd, argw );
    } catch( argumentNotFoundException& e ){
      REQUIRE( e.culprit() == string( "b" ) );
      unspecifiedSanity = true;
    }

    REQUIRE( unspecifiedSanity );
  }

  SECTION( "Determines when not enough arguments are given" ){
    bool notEnoughSanity = false;

    ap.add_argument( "--htns", "", 4 );

    try{
      ap.parse_args( argd, argw );
    } catch( incorrectParameterCountException& ){
      notEnoughSanity = true;
    }

    REQUIRE( notEnoughSanity );
  }

  SECTION( "Arguments can be checked after parsing" ){
    ap.parse_args( --argd, argw );
    auto htns = ap.get_argument<wrapper<2>>( "--htns" );

    REQUIRE( ap.get_argument<string>( "--test" ) == string( "a" ) );
    REQUIRE( ap.get_argument<wrapper<1>>( "--str" ).get() == string( "test" ) );

    REQUIRE( htns.get( 0 ) == string( "abc" ) );
    REQUIRE( htns.get( 1 ) == string( "xyz" ) );

    REQUIRE( ap.get_argument<int>( "--aoeu" ) == 1 );
    REQUIRE( ap.get_argument<bool>( "-test" ) );

    REQUIRE( ap.get_argument<int>( "--default" ) == 12 );
  }
}

