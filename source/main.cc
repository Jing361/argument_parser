#include<iostream>
#include<string>
#include<exception>

#include<argparse.hh>

using namespace std;

int main(int argc, char** argv){
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
}

