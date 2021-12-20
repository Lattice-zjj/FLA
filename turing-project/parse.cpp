#include "parse.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

std::regex Parse::Q_regex("#Q = \\{\\w+(,\\w+)*\\}");
std::regex Parse::S_regex("#S = \\{[^\\s,;\\{\\}\\*_](,[^\\s,;\\{\\}\\*_])*\\}");
std::regex Parse::G_regex("#G = \\{[^\\s,;\\{\\}\\*](,[^\\s,;\\{\\}\\*])*\\}");
std::regex Parse::q0_regex("#q0 = \\w+");
std::regex Parse::B_regex("#B = _");
std::regex Parse::F_regex("#F = \\{\\w+(,\\w+)*\\}");
std::regex Parse::N_regex("#N = [1-9]\\d*");
std::regex Parse::T_regex("\\w+ [^\\s,;\\{\\}]+ [^\\s,;\\{\\}]+ [rl\\*]+ \\w+\\s*");

const std::vector<std::string> split(const std::string &str, const char &delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string tok;

    while (std::getline(ss, tok, delimiter)) {
        result.push_back(tok);
    }
    return result;
}
Parse::Parse(std::string filename) {
    this->filename = filename;
    
    init();
}

bool Parse::dosolve() {
    fstream infile(filename, ios::in);
    if (!infile.is_open()) {
        std::cerr << "Turing:"
                  << " \033[31merror:\033[0m" << filename<<": No such file or directory" << std::endl;
        return false;
    }
    int lineno = 0;
    while (!infile.eof())
    {
        lineno++;
        string line;
        getline(infile, line);
        string str = line.substr(0, line.find(';'));
        if (str.empty()) continue; 
        if (str[0] == '#') {
            if (str[1] == 'Q') {
                // cout << str << std::endl;
                if (!regex_match(str, Q_regex)) {
                    this->printError(lineno, filename, line, "Q is error!");
                    return false;
                }
                this->fileillegal["Q"].first = true;
                this->Q = parse_QF(line);
                sort(Q.begin(), Q.end());
                if (!(std::unique(Q.begin(), Q.end()) == Q.end()))
                {
                    this->printError(lineno, filename, line, "State in Q is repeated");
                    return false;
                }
            }
            else if (str[1] == 'S') {
                if (!regex_match(str, S_regex)) {
                    this->printError(lineno, filename, line, "S is error!");
                    return false;
                }
                this->fileillegal["S"].first = true;
                this->S = parse_SG(line);
                sort(S.begin(), S.end());
                if (!(std::unique(S.begin(), S.end()) == S.end()))
                {
                    this->printError(lineno, filename, line, "symbols in S is repeated");
                    return false;
                }
            }
            else if (str[1] == 'G') {
                if (!regex_match(str, G_regex)) {
                    this->printError(lineno, filename, line, "G is error!");
                    return false;
                }
                this->fileillegal["G"].first = true;
                this->G = parse_SG(line);
                for (auto ss: this->S) {
                    if (find(G.begin(), G.end(),ss)==G.end()) {
                        this->printError(lineno, filename, line, "the tape symbols should contains input symbols!");
                        return false;
                    }
                }
                sort(G.begin(), G.end());
                if (!(std::unique(G.begin(), G.end()) == G.end()))
                {
                    this->printError(lineno, filename, line, "symbols in G is repeated");
                    return false;
                }
            }
            else if (str[1] == 'q' && str[2] == '0') {
                if (!regex_match(str, q0_regex)) {
                    this->printError(lineno, filename, line, "q0 is error!");
                    return false;
                }
                this->fileillegal["q0"].first = true;
                parse_q0(line);
                if (find(Q.begin(), Q.end(),this->q0)==Q.end()) {
                    this->printError(lineno, filename, line, "start state should in Q!");
                    return false;
                }
            }
                
            else if (str[1] == 'B'){
                if (!regex_match(str, B_regex)) {
                    this->printError(lineno, filename, line, "B is error!");
                    return false;
                }
                this->fileillegal["B"].first = true;
                parse_B(line);
                if (this->B!='_') {
                    this->printError(lineno, filename, line, "in this lab the blank symbol should be '_'!");
                    return false;
                }
            }
                
            else if (str[1] == 'F') {
                if (!regex_match(str, F_regex)) {
                    this->printError(lineno, filename, line, "F is error!");
                    return false;
                }
                this->fileillegal["F"].first = true;
                this->F = parse_QF(line);
                for (auto finalstate:this->F) {
                    if (find(Q.begin(), Q.end(),finalstate)==Q.end()) {
                         this->printError(lineno, filename, line, "final state should in Q!");
                        return false;
                    }
                }
                sort(F.begin(), F.end());
                if (!(std::unique(F.begin(), F.end()) == F.end()))
                {
                    this->printError(lineno, filename, line, "State in F is repeated");
                    return false;
                }
            }
            else if (str[1] == 'N') {
                if (!regex_match(str, N_regex)) {
                    this->printError(lineno, filename, line, "N is error!");
                    return false;
                }
                this->fileillegal["N"].first = true;
                parse_N(line);
                if (this->N <= 0) {
                    this->printError(lineno, filename, line, "the number of tapes should larger than 0!");
                    return false;
                }
                
            }
                
            else {
                
                std::cerr << filename << ":" << lineno << "\033[31m error:\033[0m '" << line[1] << "' is wrong; did you mean 'Q/S/G/q0/B/F/N'?" << std::endl;
                std::cerr << setiosflags(ios::right) << setw(5) << lineno << " |" << line << endl;
                std::cerr << "      "
                          << "| "
                          << "\033[31m^\033[0m"<< std::endl;
                return false;
            }
        } else{
            // cout << str;
            if (!regex_match(str, T_regex))
            {
                this->printError(lineno, filename, line, "transition functions is error!");
                return false;
            }
            this->fileillegal["T"].first = true;
            str.erase(str.find_last_not_of(" ") + 1);
            vector<string> result = split(str, ' ');
            // cout << str << " " << result.size() << endl;
            if (!this->checkTransform(result,lineno,filename,line)) return false;
            string current_state = result[0];
            string current_tape = result[1];
            Transform transform(result[2], result[3], result[4]);
            // cout << current_state << " " << current_tape << endl;
            // warning: transform
            this->transRules[std::pair<string, string>(current_state, current_tape)] = transform;
            // cout<<transform.lr << std::endl;
        }
    }
    map<string, pair<bool, string>>::iterator iter;
    bool flagtrue = true;
    for (iter = this->fileillegal.begin(); iter != this->fileillegal.end(); iter++)
    {
        if (iter->second.first==false) {
            std::cerr << "Turing:"
                      << " \033[31merror:\033[0m did you lose" << iter->second.second << "/‘" << iter->first << "’?" << std::endl;
            flagtrue = false;
        }
    }
    return flagtrue;
}
vector<string> Parse::parse_QF(string str){
    vector<string> ans;
    str = str.substr(str.find('{') + 1, str.find('}') - str.find('{') - 1);
    ans = split(str, ',');
    return ans;
}
vector<char> Parse::parse_SG(string str){
    str = str.substr(str.find('{') + 1, str.find('}') - str.find('{')-1);
    vector<char> ans;
    auto result = split(str, ',');
    for (auto characters : result){
        ans.push_back(characters[0]);
        // cout << characters[0] << " " << endl;
    }
    return ans;
}
void Parse::parse_q0(string str){
    str = str.substr(str.find("= ") + 2);
    this->q0 = str;
}
void Parse::parse_B(string str){
    str = str.substr(str.find("= ") + 2);
    this->B = str[0];
}
void Parse::parse_N(string str){
    str = str.substr(str.find('=') + 1);
    stringstream ss(str);
    ss >> this->N;
}

void Parse::printError(int lineno,string filename, string line,string warning){
    std::cerr << filename << ":" << lineno << "\033[31m error:\033[0m "
                          << warning << std::endl;
                std::cerr << setiosflags(ios::right) << setw(5) << lineno << " | \033[31m" << line <<"\033[0m" << endl;
                std::cerr << "      "
                          << "| "
                          << "\033[31m^\033[0m"<< std::endl;
}

bool Parse::checkTransform(vector<string> result,int lineno, string filename, string line){
    if (this->N == 0) {
        std::cerr << "N is not defined here, please check the position of N!" << endl;
        return false;
    }
    if (result.size() != 5){
        this->printError(lineno, filename, line, "something wrong with the transform rules, the number of it isn't 5.");
        return false;
    }
    string nowState = result.at(0);
    string nextState = result.at(4);
    if (find(Q.begin(), Q.end(), nowState) == Q.end() || find(Q.begin(), Q.end(), nextState) == Q.end()) {
        this->printError(lineno, filename, line, "something wrong with the transform rules, State isn't in Q!");
        return false;
    }
    string all = result.at(1) + result.at(2);
    for (char ch:all) {
        if (find(G.begin(), G.end(), ch)==G.end() && ch!='*') {
            this->printError(lineno, filename, line, "something wrong with the transform rules, symbols is not in the tape set!");
            return false;
        }
    }
    string l_and_r = result.at(3);
    for (char ch:l_and_r){
        if (ch != 'l'&& ch!='r'&&ch!='*') {
            this->printError(lineno, filename, line, "something wrong with the transform rules, move symbols is not correct, must be 'l/r/*'");
            return false;
        }
    }
    if (result.at(1).length()!=this->N || result.at(2).length()!=this->N || result.at(3).length()!=this->N) {
        this->printError(lineno, filename, line, "something wrong with the transform rules, isn't match with tapes number.");
        return false;
    }
    return true;
}


void Parse::init() {
    this->fileillegal["Q"] = make_pair<bool, string>(false, "the finite set of states");
    this->fileillegal["S"] = make_pair<bool, string>(false, "the finite set of input symbols");
    this->fileillegal["G"] = make_pair<bool, string>(false, "the complete set of tape symbols");
    this->fileillegal["q0"] = make_pair<bool, string>(false, "the start state");
    this->fileillegal["B"] = make_pair<bool, string>(false, "the blank symbol");
    this->fileillegal["F"] = make_pair<bool, string>(false, "the set of final states");
    this->fileillegal["N"] = make_pair<bool, string>(false, "the number of tapes");
    this->fileillegal["T"] = make_pair<bool, string>(false, "the transition functions");
}