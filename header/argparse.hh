#ifndef __ARGPARSE_HH__
#define __ARGPARSE_HH__

#include<vector>
#include<map>
#include<string>
#include<sstream>

class argument{
private:
  std::string mData;

public:
  template<class T>
  T retrieve(){
    std::stringstream ss(mData);
    T t;

    ss >> t;

    return t;
  }
};

class argparse{
private:
  std::vector<std::string> mSingleTokens;
  std::vector<std::string> mDoubleTokens;
  std::map<std::string, argument> mArgs;

public:
  void parse_args(int argc, char** argv);
  void add_argument(std::string name);
  template<class T>
  T get_argument(std::string name){
    return mArgs[name].retrieve<T>();
  }
};

#endif

