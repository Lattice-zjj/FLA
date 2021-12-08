#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "parse.h"
#include "TM.h"
using namespace std;

bool verbose = false;

void print_error(string);

int main(int argc, char** argv){
    vector<string> arguments;
    vector<string> others;
    string otherss = "";
    for (int i = 1; i < argc; i++)
    {
        string argument = argv[i];
        if (argument[0] == '-') 
            arguments.push_back(argument);
        else {
            others.push_back(argument);
            otherss += argument + " ";
        }
    }
    for (auto argument : arguments) {
        if (argument == "-v" || argument == "--verbose") {
            verbose = true;
        }
        else if (argument =="-h" || argument == "--help") {
            cout << "\033[32mturing: usage\033[0m: [-v|--verbose] [-h|--help] <tm> <input>" << std::endl;
            return 0;
        }
        else {
            print_error(argument);
            return 1;
        }
    }
    if (others.size() == 2) {
        string filename = others.at(0); // get the filename
        Parse parse(filename);
        parse.dosolve();

        TM tm(parse);
        string str = others.at(1);
        if (!tm.dosolve(str)) return 1;
    }
    else {
        print_error(otherss);
        return 1;
    }
    

    return 0;

}

void print_error(string error) {
    cerr << "turing: "
         << "\033[31merror:\033[0m"
         << " unrecognized command line option ‘"
         << "\e[1m" << error << "\e[0m"
         << "’" << std::endl;
    cerr << "\033[32mturing: usage\033[0m: [-v|--verbose] [-h|--help] <tm> <input>" << std::endl;
}