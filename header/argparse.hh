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

public:
  argumentNotFoundException(std::string name);

  virtual const char* what() const noexcept;
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
  notEnoughParametersException(std::string argument, int narg);

  virtual const char* what() const noexcept;
};

class argument{
private:
  unsigned int mNargs;
  std::string mData;

public:
  argument();
  argument(unsigned int nargs);

  std::string& getValue();
  unsigned int getNargs();
};

class argparse{
private:
  std::vector<std::string> mSingleTokens;
  std::vector<std::string> mDoubleTokens;
  std::map<std::string, argument> mArgs;

public:
  void parse_args(int argc, char** argv);
  void add_argument(std::string name, unsigned int narg = 0);
  template<class T>
  T get_argument(std::string name){
    try{
      mArgs.at(name);
    } catch(std::exception& e){
      throw argumentNotFoundException(name);
    }

    std::stringstream ss(mArgs[name].getValue());
    std::string dump;
    ss >> dump;

    T t;

    ss >> t;

    return t;
  }
};

template<>
inline bool argparse::get_argument<bool>(std::string name){
  try{
    if(mArgs.at(name).getValue() != ""){
      return true;
    } else {
      return false;
    }
  } catch(std::exception& e){
    throw argumentNotFoundException(name);
  }

}

#endif

