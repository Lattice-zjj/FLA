#include "parse.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

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
}

bool Parse::dosolve() {
    fstream infile(filename, ios::in);
    while (!infile.eof()) {
		string line;
		getline(infile, line);
        string str = line.substr(0, line.find(';'));
        // std::cout << str << std::endl;
        if (str.empty()) continue; 
        if (str[0] == '#') {
            switch (str[1]) {
                case 'Q':
                    this->Q = parse_QF(line);
                    break;
                case 'S':
                    this->S = parse_SG(line);
                    break;
                case 'G':
                    this->G = parse_SG(line);
                    break;
                case 'q':
                    parse_q0(line);
                    break;
                case 'B':
                    parse_B(line);
                    break;
                case 'F':
                    this->F = parse_QF(line);
                    break;
                case 'N':
                    parse_N(line);
                    break;
                default:
                    break;
                }
        }
    }
    return true;
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