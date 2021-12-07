#ifndef TM_H
#define TM_H
#include <iostream>
#include <string>
#include <vector>
#include "parse.h"
using namespace std;


class TM {
public:
    TM(Parse parse);
    void dosolve(string);

private:
    


    vector<string> Q;
    vector<char> S;
    vector<char> G;
    string q0;
    char B;
    vector<string> F;
    int N;
    map<pair<string, string>, Transform> transRules;
};

#endif // TM_H