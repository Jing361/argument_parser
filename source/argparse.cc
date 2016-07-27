#include<sstream>
#include<argparse.hh>

using namespace std;

argumentNotFoundException::argumentNotFoundException(std::string name):
  mArgName(name){
}

const char* argumentNotFoundException::what() const noexcept{
  return ("Could not find " + mArgName + ".").c_str();
}

argument::argument(){
}

argument::argument(unsigned int nargs):
  mNargs(nargs){
}

std::string& argument::getValue(){
  return mData;
}

void argparse::parse_args(int argc, char** argv){
  string str;
  for(;argc > 0; --argc){
    str += argv[argc - 1];
    str += ' ';
  }

  stringstream ss(str);

  string tok;
  while(ss >> tok){
    if(tok[0] == '-'){
      if(tok[1] == '-'){
      } else {
        try{
          mArgs.at(tok);
        } catch (std::exception& e){
          throw argumentNotFoundException(tok);
        }
        mArgs[tok].getValue() = tok.substr(2);
      }
    }
  }
}

void argparse::add_argument(std::string name, unsigned int narg){
  mArgs[name] = argument(narg);
}

