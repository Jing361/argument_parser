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
  const string& get() const{
    return mStr;
  }
};

istream& operator>>(istream& is, wrapper& w){
  string str;

  is >> str;

  w = wrapper(str);

  return is;
}

class doublewide{
private:
  string val1;
  string val2;

public:
  doublewide() = default;
  doublewide(string str1, string str2):
    val1(str1),
    val2(str2){
  }
  const string& get1() const{
    return val1;
  }
  const string& get2() const{
    return val2;
  }
};

istream& operator>>(istream& is, doublewide& w){
  string str1;
  string str2;

  is >> str1;
  is >> str2;

  w = doublewide(str1, str2);

  return is;
}

TEST_CASE("Arguments can be checked by existence", "[parser]"){
  argparse ap;
  const char* argw[] = { "main", 
                         "--test", "a",
                         "--aoeu", "1",
                         "--htns", "abc", "xyz",
                         "--str", "test",
                         "-test", "b" };
  int argd = 12;

  ap.add_argument("--test", "", 1);
  ap.add_argument("--aoeu", "", 1);
  ap.add_argument("--htns", "", 2);
  ap.add_argument("--str", "", 1);
  ap.add_argument("--default", "12", 1);
  ap.add_argument("-test");
  ap.add_argument("none");

  SECTION("Catches unspecified arguments"){
    bool sanity = false;
    try{
      ap.parse_args(argd, argw);
    } catch(argumentNotFoundException& e){
      REQUIRE(e.culprit() == string("b"));
      sanity = true;
    }
    REQUIRE(sanity);
  }

  SECTION("Arguments can be checked after parsing"){
    ap.parse_args(--argd, argw);

    REQUIRE(ap.get_argument<string>("--test") == string("a"));
    REQUIRE(ap.get_argument<wrapper>("--str").get() == string("test"));

    REQUIRE(ap.get_argument<doublewide>("--htns").get1() == string("abc"));
    REQUIRE(ap.get_argument<doublewide>("--htns").get2() == string("xyz"));

    REQUIRE(ap.get_argument<int>("--aoeu") == 1);
    REQUIRE(ap.get_argument<bool>("-test"));

    REQUIRE(ap.get_argument<int>("--default") == 12);
  }
}

