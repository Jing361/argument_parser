#ifndef __ARGPARSE_HH__
#define __ARGPARSE_HH__

#include<vector>
#include<map>
#include<string>
#include<sstream>
#include<exception>

class argumentNotFoundException : public std::exception{
private:
  std::string mMessage;
  std::string mCulprit;

public:
  argumentNotFoundException( std::string name );

  virtual const char* what() const noexcept;

  virtual const char* culprit() const noexcept;
};

class invalidTypeException : public std::exception{
private:
  std::string mMessage;

public:
  invalidTypeException();
};

class notEnoughParametersException : public std::exception{
private:
  std::string mMessage;

public:
  notEnoughParametersException( std::string argument, int narg );

  virtual const char* what() const noexcept;
};

class argument{
private:
  unsigned int mNargs;
  std::string mData;

public:
  argument();
  argument( unsigned int nargs, const std::string& defVal );

  std::string getValue();
  void setValue( const std::string& str );
  unsigned int getNargs();
};

class argparse{
private:
  std::vector<std::string> mSingleTokens;
  std::vector<std::string> mDoubleTokens;
  std::map<std::string, argument> mArgs;

public:
  void parse_args( int argc, const char** argv );
  void add_argument( std::string name, std::string defVal = "", unsigned int narg = 0 );
  template<class T>
  T get_argument( const std::string& name ){
    try{
      mArgs.at( name );
    } catch( std::exception& e ){
      throw argumentNotFoundException( name );
    }

    std::stringstream ss( mArgs[name].getValue() );
    std::string dump;

    ss >> dump;

    T t;

    ss >> t;

    return t;
  }
};

/* this specialization depends on the value returned from getvalue to be not 
 * empty when the value was found.  the simple solution is to always prepend
 * the value with the argument name when it is found.
 */
template<>
inline bool argparse::get_argument<bool>( const std::string& name ){
  try{
    if( mArgs.at( name ).getValue() != "" ){
      return true;
    } else {
      return false;
    }
  } catch( std::exception& e ){
    throw argumentNotFoundException( name );
  }
}

#endif

