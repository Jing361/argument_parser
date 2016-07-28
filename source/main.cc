#include<iostream>
#include<string>
#include<exception>

#define CATCH_CONFIG_MAIN
#include<catch/catch.hpp>

#include<argparse.hh>

using namespace std;

TEST_CASE("Arguments can be checked by existence", "[parser]"){
  argparse ap;
  const char* argw[] = { "main", 
                         "--test", "a",
                         "-test", "b" };
  int argd = 5;

  ap.add_argument("--test", 1);
  ap.add_argument("-test");
  ap.add_argument("none");

  SECTION("Catches unspecified arguments"){
    try{
      ap.parse_args(argd, argw);
    } catch(argumentNotFoundException& e){
      REQUIRE(e.culprit() == string("b"));
    }
  }

  SECTION("Arguments can be checked after parsing"){
    ap.parse_args(--argd, argw);

    REQUIRE(ap.get_argument<string>("--test") == string("a"));
    REQUIRE(ap.get_argument<bool>("-test"));
  }
}

