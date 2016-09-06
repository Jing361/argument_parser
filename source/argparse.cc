#include<iostream>
#include<sstream>
#include<argparse.hh>

using namespace std;

argumentNotFoundException::argumentNotFoundException(std::string name):
  mMessage("Could not find argument \"" + name + "\"."),
  mCulprit(name){
}

const char* argumentNotFoundException::what() const noexcept{
  return mMessage.c_str();
}

const char* argumentNotFoundException::culprit() const noexcept{
  return mCulprit.c_str();
}

invalidTypeException::invalidTypeException():
  mMessage("Invalid type for this argument"){
}

notEnoughParametersException::notEnoughParametersException(std::string argument, int narg):
  mMessage("Not enough arguments supplied for \"" + argument + "\".  Expected "
           + to_string(narg) + "."){
}

const char* notEnoughParametersException::what() const noexcept{
  return mMessage.c_str();
}

argument::argument():
  argument(0, ""){
}

argument::argument(unsigned int nargs, const std::string& defVal):
  mNargs(nargs),
  mData(defVal){
}

std::string argument::getValue(){
  return mData;
}

void argument::setValue(const std::string& str){
  if( str != "" ){
    mData = str;
  }
}

unsigned int argument::getNargs(){
  return mNargs;
}

void argparse::parse_args(int argc, const char** argv){
  string str;
  for(int i = 1; i < argc; ++i){
    str += argv[i];
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
        mArgs[tok].setValue( tok.substr(2) );
      } else {
        mArgs[tok].setValue( tok.substr(1) );
      }
    }

    unsigned int i = 0;
    while(i++ < mArgs[tok].getNargs()){
      string param;
      if(ss >> param){
        if(param[0] == '-'){
          throw notEnoughParametersException(tok, mArgs[tok].getNargs());
        }
        mArgs[tok].setValue( mArgs[tok].getValue() + ' ' );
        mArgs[tok].setValue( mArgs[tok].getValue() + param );
      } else {
        throw notEnoughParametersException(tok, mArgs[tok].getNargs());
      }
    }
  }
}

void argparse::add_argument(std::string name, std::string defVal, unsigned int narg){
  mArgs[name] = argument(narg, name + ' ' + defVal);
}

