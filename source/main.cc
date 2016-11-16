#include<iostream>
#include<string>
#include<exception>
#include<array>

#define CATCH_CONFIG_MAIN
#include<catch/catch.hpp>

#include<argparse.hh>

using namespace std;

template<unsigned int N>
class wrapper{
private:
  array<string, N> mArr;

public:
  wrapper() = default;
  wrapper( const array<string, N>& arr ){
    mArr = arr;
  }
  const string& get( unsigned int idx = 0 ) const{
    return mArr[idx];
  }
};

template<unsigned int N>
istream& operator>>( istream& is, wrapper<N>& w ){
  array<string, N> arr;

  for( auto& it : arr ){
    is >> it;
  }

  w = wrapper<N>( arr );

  return is;
}

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
    bool sanity = false;
    try{
      ap.parse_args( argd, argw );
    } catch( argumentNotFoundException& e ){
      REQUIRE( e.culprit() == string( "b" ) );
      sanity = true;
    }
    REQUIRE( sanity );
  }

  SECTION( "Determines when not enough arguments are given" ){
  }

  SECTION( "Arguments can be checked after parsing" ){
    ap.parse_args( --argd, argw );

    REQUIRE( ap.get_argument<string>( "--test" ) == string( "a" ) );
    REQUIRE( ap.get_argument<wrapper<1>>( "--str" ).get() == string( "test" ) );

    auto htns = ap.get_argument<wrapper<2>>( "--htns" );
    REQUIRE( htns.get( 0 ) == string( "abc" ) );
    REQUIRE( htns.get( 1 ) == string( "xyz" ) );

    REQUIRE( ap.get_argument<int>( "--aoeu" ) == 1 );
    REQUIRE( ap.get_argument<bool>( "-test" ) );

    REQUIRE( ap.get_argument<int>( "--default" ) == 12 );
  }
}

