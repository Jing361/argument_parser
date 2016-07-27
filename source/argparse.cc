#include<sstream>
#include<argparse.hh>

using namespace std;

argumentNotFoundException::argumentNotFoundException(std::string name):
  mMessage("Could not find parametr " + name + "."){
}

const char* argumentNotFoundException::what() const noexcept{
  return mMessage.c_str();
}

invalidTypeException::invalidTypeException():
  mMessage("Invalid type for this argument"){
}

argument::argument(){
}

argument::argument(unsigned int nargs):
  mNargs(nargs){
}

std::string& argument::getValue(){
  return mData;
}

unsigned int argument::getNargs(){
  return mNargs;
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
    try{
      mArgs.at(tok);
    } catch (std::exception& e){
      throw argumentNotFoundException(tok);
    }
    if(tok[0] == '-'){
      if(tok[1] == '-'){
        mArgs[tok].getValue() = tok.substr(2);
      } else {
        mArgs[tok].getValue() = tok.substr(2);
      }
    }

    unsigned int i = 0;
    while(ss >> tok && i < mArgs[tok].getNargs()){
      mArgs[tok].getValue() += ' ' + tok;
    }
  }
}

void argparse::add_argument(std::string name, unsigned int narg){
  mArgs[name] = argument(narg);
}

