#include "TM.h"

TM::TM(Parse parse){
    this->Q = parse.Q;
    this->S = parse.S;
    this->G = parse.G;
    this->q0 = parse.q0;
    this->B = parse.B;
    this->F = parse.F;
    std::cout << this->F.size() << std::endl;
    this->N = parse.N;
    // std::cout << this->N << std::endl;
}