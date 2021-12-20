#include "TM.h"
#include <unistd.h>
extern bool verbose;
extern bool StepByStep;
TM::TM(Parse parse)
{
    this->Q = parse.Q;
    this->S = parse.S;
    this->G = parse.G;
    this->q0 = parse.q0;
    this->B = parse.B;
    this->F = parse.F;
    this->N = parse.N;
    this->transRules = parse.transRules;
}

bool TM::dosolve(string input) {
    if (!isIllegal(input)) return false;
    if (verbose) {
        std::cout << "Correct" << std::endl;
        std::cout << "==================== RUN ====================" << std::endl;
    }
    ID id(this->N, input, this->q0);
    if (verbose) id.display();
    bool Stop = true;
    while (Stop)
    {
        if (StepByStep) sleep(1);
        id.step++;
        string nowTape = "";
        for (int tapeIndex = 0; tapeIndex < this->N; tapeIndex++)
            for (long unsigned int j = 0; j < id.tapes[tapeIndex].size();j++) 
                if (id.headIndex[tapeIndex] == id.Index[tapeIndex].at(j))
                    nowTape += id.tapes[tapeIndex].at(j);
        // cout << nowTape << std::endl;
        string nowState = id.nowState;
        // cout<<nowState << std::endl;
        map<pair<string, string>, Transform>::iterator it;
        int max = -1;
        Transform tmp;
        bool isFind = false;
        for (it = this->transRules.begin(); it != this->transRules.end(); it++)
        {
            pair<string, string> first = it->first;
            if (first.first == nowState) {
                bool flag = true;
                int match = 0;
                string expectedTape = first.second;
                for (long unsigned int j = 0; j <expectedTape.size(); j++) {
                     if (expectedTape[j] != nowTape[j]) {
                        if (expectedTape[j] != '*') {
                            flag = false;
                            break;
                        }
                     } 
                     else match++;
                }
                if (match > max && flag) {
                    max = match;
                    isFind = true;
                    tmp = it->second;
                }
            }
        }
        if (!isFind) {
            break;
        }
        id.nowState = tmp.next;

        //开始转移
        string write = tmp.write, lr = tmp.lr;
        // cout<<write<< std::endl;
        for (int tapeIndex = 0; tapeIndex < this->N; tapeIndex++) {

            char WriteChar = write[tapeIndex], LR = lr[tapeIndex];
            if (WriteChar != '*')
                for (long unsigned int j = 0; j < id.tapes[tapeIndex].size();j++) 
                    if (id.headIndex[tapeIndex] == id.Index[tapeIndex].at(j))
                        id.tapes[tapeIndex].at(j) = WriteChar;
            if (LR == '*') continue;
            if (LR == 'l') {
                if (id.headIndex[tapeIndex] == id.Index[tapeIndex].at(0)) {
                    id.headIndex[tapeIndex]--;
                    id.Index[tapeIndex].push_front(id.headIndex[tapeIndex]);
                    id.tapes[tapeIndex].push_front('_');
                }
                else 
                    id.headIndex[tapeIndex]--;
            }
            else if (LR == 'r') {
                if (id.headIndex[tapeIndex] == id.Index[tapeIndex].at(id.Index[tapeIndex].size() - 1)) {
                    id.headIndex[tapeIndex]++;
                    id.Index[tapeIndex].push_back(id.headIndex[tapeIndex]);
                    id.tapes[tapeIndex].push_back('_');
                }
                else 
                    id.headIndex[tapeIndex]++;
            }
        }

        // cout << tmp.next << endl;
        if (verbose) id.display();
        // break;
        // check whether nowState is stoped
        Stop = this->checkStop(id.nowState);
        // cout << Stop;
    }

    string result = "";
    int len = id.tapes[0].size();
    int start;
    for (start = 0; start < len; start++){
        if (!(id.tapes[0].at(start) == '_')) break;
    }
    int end;
    for (end = len - 1; end >= 0; end--){
        if (!(id.tapes[0].at(end) == '_')) break;
    }
    for (int j = start; j <= end; j++){
        result += id.tapes[0].at(j);
    }
    if (verbose) {
        cout << "Result  :    " << result << endl;
        cout << "==================== END ===============" << endl;
    }
    else
        cout << result << endl;
    return true;
}

bool TM::isIllegal(string input) {
    int len = input.length();
    if (verbose) cout << "Input: " << input << endl;
    // check whether input is illegal.
    for (int i = 0; i < len; i++) {
		vector<char>::iterator it = find(this->S.begin(),this->S.end(),input[i]);
        if (it == this->S.end())
        {
            if (verbose) {
                char characters = input[i];
                std::cerr << "==================== ERR ====================" << endl;
                std::cerr << "\033[31merror: \033[0m'"<<characters<<"' was not declared in the set of input symbols"<< std::endl;
                std::cerr << "Input: " << input.substr(0,i)<<"\033[31m"<<characters<<"\033[0m" <<input.substr(i+1) << endl;
                std::cerr << "\033[31m"<<setiosflags(ios::right) << setw(i + 8) << "^" <<"\033[0m"<< std::endl;
                std::cerr << "==================== END ====================" << endl;
            }
            else
                std::cerr << "illegal input" << std::endl;
            return false;
        }
    }
    return true;
}

bool TM::checkStop(string nowState){
    // cout << "nowstate:" << nowState<<endl;
    // cout << F.size()<<" "<<F[0] << endl;
    vector<string>::iterator it = find(this->F.begin(), this->F.end(), nowState);
    return it == this->F.end();
}