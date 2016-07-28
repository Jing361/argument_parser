#include<iostream>
#include<string>

#include<argparse.hh>

using namespace std;

int main(int argc, char** argv){
  argparse ap;

  ap.add_argument("--test", 1);
  ap.add_argument("-test");
  ap.parse_args(argc, argv);
  cout << ap.get_argument<string>("--test") << endl;
  cout << ap.get_argument<string>("-test") << endl;
  cout << ap.get_argument<string>("fail") << endl;

  return 0;
}

