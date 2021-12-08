#include "ID.h"

ID::ID(int num, string input, string start) {
    this->num = num;
    this->step = 0;
    this->nowState = start;
    for (int i = 0; i < num; i++)
    {
        this->headIndex.push_back(0);
        this->tapes.push_back(deque<char>());
        this->Index.push_back(deque<int>());
    }
    for (long unsigned int i = 0; i < input.size(); i++) {
        this->tapes[0].push_back(input[i]);
        this->Index[0].push_back(i);
    }
    for (int i = 1; i < num; i++) {
        this->tapes[i].push_back('_');
        this->Index[i].push_back(0);
	}
}

void ID::display() {
    cout << "Step	:    " << setiosflags(ios::left) << setw(5) << this->step << endl;
    for (int i = 0; i < this->num; i++)
    {
        int len = this->tapes[i].size();
        int start;
        for (start = 0; start < len; start++){
            if (!(this->tapes[i].at(start) == '_' && this->headIndex[i]>this->Index[i].at(start))) break;
        }
        int end;
        for (end = len - 1; end >= 0; end--){
            if (!(this->tapes[i].at(end) == '_' && this->headIndex[i]<this->Index[i].at(end))) break;
        }
        // cout << "\033[31m" << start << " " << end << "\033[0m" << std::endl;
        cout << "Index" << i << "	:    ";
        for (int j = start; j <= end;j++) {
            int index;
            if (this->Index[i].at(j) < 0)
                index = (-1) * this->Index[i].at(j);
            else
                index = this->Index[i].at(j);
            cout << setiosflags(ios::left) << setw(5) << index;
        }
        cout << endl;

        cout << "Tape" << i << "   :    ";
        for (int j = start; j <= end; j++) {
            cout << setiosflags(ios::left) << setw(5) << this->tapes[i].at(j);
        }

        cout << endl;

        cout<< "Head" << i << "   :    ";
        for (int j = start; j <= end;j++) {
            if (this->Index[i].at(j) == this->headIndex[i])
                cout << setiosflags(ios::left) << setw(5) << "^";
            else
                cout << setiosflags(ios::left) << setw(5) << " ";
        }
        cout << endl;
    }
    cout << "State   :    " << this->nowState << endl;
    cout << "---------------------------------------------" << endl;
}