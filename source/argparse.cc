#include<argparse.hh>

using namespace std;

argparse::argparse(int argc, char** argv){
  string str;
  for(;argc > 0; --argc){
    str += argv[argc - 1];
    str += ' ';
  }

  stringstream ss(str);
  vector<string> toks;

  string tok;
  while(ss >> tok){
    if(tok[0] == '-'){
      toks.push_back(tok.substr(1));
    }
  }

  for(auto it:toks){
    if(it[0] == '-'){
      mDoubleTokens.push_back(it.substr(1));
    } else {
      mSingleTokens.push_back(it);
    }
  }
}

