#ifndef TM_H
#define TM_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class TM {
public:
    TM(vector<string> Q, vector<char> S, vector<char> G, char q0, char B, vector<string> F, int N);


private:
    vector<string> Q;
    vector<char> S;
    vector<char> G;
    char q0;
    char B;
    vector<string> F;
    int N;
};

#endif