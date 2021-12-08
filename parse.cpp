#include "parse.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
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
    int lineno = 0;
    while (!infile.eof())
    {
        lineno++;
        string line;
        getline(infile, line);
        string str = line.substr(0, line.find(';'));
        if (str.empty()) continue; 
        if (str[0] == '#') {
            if (str[1] == 'Q')
                this->Q = parse_QF(line);
            else if (str[1] == 'S')
                this->S = parse_SG(line);
            else if (str[1] == 'G')
                this->G = parse_SG(line);
            else if (str[1] == 'q' && str[2] == '0') 
                parse_q0(line);
            else if (str[1] == 'B')
                parse_B(line);
            else if (str[1] == 'F') 
                this->F = parse_QF(line);
            else if (str[1] == 'N') 
                parse_N(line);
            else {
                std::cerr << filename << ":" << lineno << "\033[31m error:\033[0m '" << line[1] << "' is wrong; did you mean 'Q/S/G/q0/B/F/N'?" << std::endl;
                std::cerr << setiosflags(ios::right) << setw(5) << lineno << " |" << line << endl;
                std::cerr << "      "
                          << "| "
                          << "\033[31m^\033[0m"<< std::endl;
                return false;
            }
        } else{
            str.erase(str.find_last_not_of(" ") + 1);
            vector<string> result = split(str, ' ');
            // cout << str << " " << result.size() << endl;
            if (result.size() != 5)
            {
                return false;
            }
            string current_state = result[0];
            string current_tape = result[1];
            Transform transform(result[2], result[3], result[4]);
            // cout << current_state << " " << current_tape << endl;
            // warning: transform
            this->transRules[std::pair<string, string>(current_state, current_tape)] = transform;
            // cout<<transform.lr << std::endl;
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