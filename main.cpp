#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "parse.h"
#include "TM.h"
using namespace std;


int main(int argc, char** argv){
    string filename = argv[1];
    std::cout << filename << std::endl;
    Parse parse(filename);
    parse.dosolve();

    TM tm(parse);

    std::cout<<"\033[31mHello \033[34mworld!\033[0m"<<std::endl;
}