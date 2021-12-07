#include "TM.h"

TM::TM(Parse parse){
    this->Q = parse.Q;
    this->S = parse.S;
    this->G = parse.G;
    this->q0 = parse.q0;
    this->B = parse.B;
    this->F = parse.F;
    this->N = parse.N;
    this->transRules = parse.transRules;
}

void TM::dosolve(string input) {

}