#include<iostream>

#include<argparse.hh>

using namespace std;

int main(int argc, char** argv){
  argparse ap;

  ap.add_argument("--test");
  ap.add_argument("-test");
  ap.parse_args(argc, argv);
  cout << ap.get_argument<bool>("--test") << endl;
  cout << ap.get_argument<bool>("fail") << endl;

  return 0;
}

