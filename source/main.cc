#include<iostream>
#include<string>
#include<exception>

#define CATCH_CONFIG_MAIN
#include<catch/catch.hpp>

#include<argparse.hh>

using namespace std;

class wrapper{
private:
  string mStr;

public:
  wrapper() = default;
  wrapper(string str):
    mStr(str){
  }
  const string& get(){
    return mStr;
  }
};

istream& operator>>(istream& is, wrapper& wrap){
  string str;

  is >> str;

  wrapper w(str);
  wrap = w;

  return is;
}

TEST_CASE("Arguments can be checked by existence", "[parser]"){
  argparse ap;
  const char* argw[] = { "main", 
                         "--test", "a",
                         "--aoeu", "1",
                         "--str", "test",
                         "-test", "b" };
  int argd = 9;

  ap.add_argument("--test", 1);
  ap.add_argument("--aoeu", 1);
  ap.add_argument("--str", 1);
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
    REQUIRE(ap.get_argument<wrapper>("--str").get() == string("test"));
    REQUIRE(ap.get_argument<int>("--aoeu") == 1);
    REQUIRE(ap.get_argument<bool>("-test"));
  }
}

