
#include<argparse.hh>

using namespace std;

int main(int argc, char** argv){
  argparse ap;

  ap.add_argument("aoeu");
  ap.parse_args(argc, argv);

  return 0;
}

