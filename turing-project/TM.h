#ifndef TM_H
#define TM_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "parse.h"
#include "ID.h"
using namespace std;


class TM {
public:
    TM(Parse parse);
    bool dosolve(string);

private:
    bool isIllegal(string);
    bool checkStop(string);

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