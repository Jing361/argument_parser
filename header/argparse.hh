#ifndef __ARGPARSE_HH__
#define __ARGPARSE_HH__

#include<vector>

class argparse{
private:
  std::vector<string> mSingleTokens;
  std::vector<string> mDoubleTokens;

public:
  argparse(int argc, char** argv);
};

#endif

