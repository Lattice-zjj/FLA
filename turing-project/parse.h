#ifndef PARSE_H
#define PARSE_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>
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
    void init();
    vector<string> parse_QF(string);
    vector<char> parse_SG(string);
    void parse_q0(string);
    void parse_B(string);
    void parse_F(string);
    void parse_N(string);
    void printError(int,string,string,string);
    bool checkTransform(vector<string>,int,string,string);

    string filename;
    vector<string> Q;
    vector<char> S;
    vector<char> G;
    string q0;
    char B;
    vector<string> F;
    int N;
    map<pair<string, string>, Transform> transRules;

    map<string, pair<bool, string>> fileillegal;


    static std::regex Q_regex;
    static std::regex S_regex;
    static std::regex G_regex;
    static std::regex q0_regex;
    static std::regex B_regex;
    static std::regex F_regex;
    static std::regex N_regex;
    static std::regex T_regex;
};



#endif // PARSE_H