#ifndef __ARGPARSE_HH__
#define __ARGPARSE_HH__

#include<vector>
#include<map>
#include<string>
#include<sstream>
#include<exception>
#include<array>

template<unsigned int N>
class wrapper{
private:
  std::array<std::string, N> mArr;

public:
  wrapper() = default;
  wrapper( const std::array<std::string, N>& arr ){
    mArr = arr;
  }
  const std::string& get( unsigned int idx = 0 ) const{
    return mArr[idx];
  }
};

template<unsigned int N>
std::istream& operator>>( std::istream& is, wrapper<N>& w ){
  std::array<std::string, N> arr;

  for( auto& it : arr ){
    is >> it;
  }

  w = wrapper<N>( arr );

  return is;
}

class argumentNotFoundException : public std::exception{
private:
  std::string mMessage;
  std::string mCulprit;

public:
  argumentNotFoundException( std::string name );

  virtual const char* what() const noexcept override;

  virtual const char* culprit() const noexcept;
};


class incorrectParameterCountException : public std::exception{
private:
  std::string mMessage;

public:
  incorrectParameterCountException( const std::string& argument, unsigned int actual, unsigned int minArg, unsigned int maxArg );

  virtual const char* what() const noexcept override;
};

// exception thrown when it is unknown what went wrong
// this exception is a general case and reports exactly that which is put in its constructor
class unknownException : public std::exception{
private:
  std::string mMessage;

public:
  unknownException( const std::string& argument );

  virtual const char* what() const noexcept override;
};

class argparse;

class argument{
private:
  unsigned int mMinArgs;
  unsigned int mMaxArgs;
  std::string mData;
  std::string mDescription;

  friend argparse;

public:
  argument() = default;
  argument( unsigned int minArgs, unsigned int maxArgs, const std::string& defVal, const std::string& desc = "" );

  std::string getValue();
  void setValue( const std::string& str );
  unsigned int getMinArgs();
  unsigned int getMaxArgs();
};

class argparse{
private:
  std::map<std::string, argument> mArgs;

public:
  void parse_args( int argc, const char** argv );

  std::string get_report();

  /* add_argument is overloaded in this way because the 4th argument of (string, string, uint, uint) signature defaults to the 3rd argument, and the language does not provide for this */
  void add_argument( const std::string& name, const std::string& defVal, const std::string& desc, unsigned int minArg, unsigned int maxArg );

  inline void add_argument( const std::string& name, const std::string& defVal, const std::string& desc, unsigned int minArg ){ add_argument( name, defVal, desc, minArg, minArg ); }

  inline void add_argument( const std::string& name, const std::string& defVal, const std::string& desc ){ add_argument( name, defVal, desc, 0, 0 ); }

  inline void add_argument( const std::string& name ){ add_argument( name, "", "", 0, 0 ); }

  template<class T>
  T get_argument( const std::string& name ){
    try{
      mArgs.at( name );
    } catch( std::out_of_range& ){
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
    return mArgs.at( name ).getValue() != "";
  } catch( std::out_of_range& ){
    throw argumentNotFoundException( name );
  }
}

#endif

