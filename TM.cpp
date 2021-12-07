#include "TM.h"

TM::TM(vector<string> Q, vector<char> S, vector<char> G, char q0, char B, vector<string> F, int N){
    this->Q = Q;
    this->S = S;
    this->G = G;
    this->q0 = q0;
    this->B = B;
    this->F = F;
    this->N = N;
}