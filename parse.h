#ifndef PARSE_H
#define PARSE_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class Transform{
public:
    string write;
    string lr;
    string next;
    Transform() {}
    Transform(string write, string lr, string next) : 
        write(write), lr(lr), next(next){}
};

class Parse{
public:
    Parse(string);
    bool dosolve();
    friend class TM;

private:
    vector<string> parse_QF(string);
    vector<char> parse_SG(string);
    void parse_q0(string);
    void parse_B(string);
    void parse_F(string);
    void parse_N(string);

    string filename;
    vector<string> Q;
    vector<char> S;
    vector<char> G;
    string q0;
    char B;
    vector<string> F;
    int N;
    map<pair<string, string>, Transform> transRules;
};

#endif // PARSE_H