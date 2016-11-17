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

incorrectParameterCountException::incorrectParameterCountException( const std::string& argument, unsigned int actual, unsigned int minArg, unsigned int maxArg ):
//TODO: make message specify what extra arguments were when too many were givin?
  mMessage("Incorrect number of arguments supplied for \"" + argument + 
           "\".  Expected at least " + to_string( minArg ) + " and at most " +
           to_string( maxArg ) + "; received " + to_string( actual ) + "." ){
}

const char* incorrectParameterCountException::what() const noexcept{
  return mMessage.c_str();
}

argument::argument(unsigned int minArgs, unsigned int maxArgs, const std::string& defVal):
  mMinArgs( minArgs ),
  mMaxArgs( maxArgs ),
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

unsigned int argument::getMinArgs(){
  return mMinArgs;
}

unsigned int argument::getMaxArgs(){
  return mMaxArgs;
}

void argparse::parse_args(int argc, const char** argv){
  string str;
  for( int i = 1; i < argc; ++i ){
    str += argv[i];
    str += ' ';
  }

  stringstream ss(str);

  string tok;
  while( ss >> tok ){
    try{
      mArgs.at( tok );
    } catch( std::out_of_range& e ){
      throw argumentNotFoundException( tok );
    }
    if( tok[0] == '-' ){
      if( tok[1] == '-' ){
        mArgs[tok].setValue( tok.substr( 2 ) );
      } else {
        mArgs[tok].setValue( tok.substr( 1 ) );
      }
    }

    unsigned int argCount = 0;
    string param;
    while( ss >> param ){
      if( param[0] == '-' ){
        for( unsigned int i = 0; i < param.size(); ++i ){
          ss.unget();
        }
        break;
      }
      ++argCount;

      mArgs[tok].setValue( mArgs[tok].getValue() + ' ' );
      mArgs[tok].setValue( mArgs[tok].getValue() + param );
    }
    //TODO: make this exception safe
    //data is modified before exception is thrown
    if( argCount < mArgs[tok].getMinArgs() || argCount > mArgs[tok].getMaxArgs() ){
      throw incorrectParameterCountException( tok, argCount, mArgs[tok].getMinArgs(), mArgs[tok].getMaxArgs() );
    }
  }
}

void argparse::add_argument( const std::string& name, std::string defVal, unsigned int minArg, unsigned int maxArg ){
  mArgs[name] = argument(minArg, maxArg, name + ' ' + defVal);
}

