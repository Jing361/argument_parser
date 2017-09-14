#include<sstream>
#include<argparse.hh>

using namespace std;

incorrectParameterCountException::incorrectParameterCountException( const string& argument, unsigned int actual, unsigned int minArg, unsigned int maxArg ):
//TODO: make message specify what extra arguments were when too many were givin?
  range_error("Incorrect number of arguments supplied for \"" + argument + 
              "\".  Expected at least " + to_string( minArg ) + " and at most " +
              to_string( maxArg ) + "; received " + to_string( actual ) + "." ){
}

unknownException::unknownException( const string& argument ):
  runtime_error( argument ){
}

argument::argument( unsigned int minArgs, unsigned int maxArgs, const string& defVal, const string& desc ):
  mMinArgs( minArgs ),
  mMaxArgs( maxArgs ),
  mData( defVal ),
  mDescription( desc ){
}

string argument::getValue(){
  return mData;
}

void argument::setValue( const string& str ){
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

void argparse::parse_args( int argc, const char** argv ){
  string str;

  for( int i = 1; i < argc; ++i ){
    str += argv[i];
    str += ' ';
  }

  stringstream ss( str );
  string tok;

  while( ss >> tok ){
    mArgs.at( tok );

    string tokenString( tok );
    unsigned int argCount = 0;
    string param;

    while( ss >> param ){
      /*! @todo find more efficient way to do this step */
      //      Could use peek? but then validity of stream isn't checked..
      if( param[0] == '-' ){
        for( auto _ : param ){
          ( void )_;
          ss.unget();
        }
        break;
      }
      ++argCount;

      tokenString += ' ' + param;
    }

    mArgs[tok].setValue( tokenString );

    /*! @todo make this exception safe */
    //data is modified before exception is thrown
    if( argCount < mArgs[tok].getMinArgs() || argCount > mArgs[tok].getMaxArgs() ){
      throw incorrectParameterCountException( tok, argCount, mArgs[tok].getMinArgs(), mArgs[tok].getMaxArgs() );
    }
  }
}

string argparse::get_report(){
  string retString;

  for( auto it : mArgs ){
    retString += it.first + "\n\t" + it.second.mDescription + "\n\n";
  }

  return retString;
}

void argparse::add_argument( const string& name, const string& defVal, const string& desc, unsigned int minArg, unsigned int maxArg ){
  string defaultText = defVal;

  if( defaultText != "" ){
    defaultText = name + ' ' + defaultText;
  }

  mArgs[name] = argument( minArg, maxArg, defaultText, desc );
}

