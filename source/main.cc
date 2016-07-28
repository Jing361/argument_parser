#include<iostream>
#include<string>
#include<exception>

#define CATCH_CONFIG_MAIN
#include<catch/catch.hpp>

#include<argparse.hh>

using namespace std;

/*int main(int argc, char** argv){
  argparse ap;

  ap.add_argument("--test", 1);
  ap.add_argument("-test");
  ap.add_argument("none");
  ap.parse_args(argc, argv);
  cout << boolalpha;
  cout << ap.get_argument<string>("--test") << endl;
  cout << ap.get_argument<bool>("-test") << endl;
  cout << ap.get_argument<bool>("none") << endl;
  try{
    cout << ap.get_argument<bool>("fail") << endl;
  } catch(std::exception& e){

  }
  try{
    cout << ap.get_argument<string>("fail") << endl;
  } catch(std::exception& e){

  }

  return 0;
}*/

TEST_CASE("Arguments can be checked by existence", "[parser]"){
  argparse ap;
  const char* argw[] = { "main", 
                         "--test", "a",
                         "-test", "b" };
  int argd = 5;

  ap.add_argument("--test", 1);
  ap.add_argument("-test");
  ap.add_argument("none");
  try{
  ap.parse_args(argd, argw);
  } catch(argumentNotFoundException& e){
    REQUIRE(e.culprit() == string("b"));
  }
}

