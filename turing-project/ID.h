#ifndef ID_H
#define ID_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <deque>
using namespace std;

class ID{
public:
    ID(int, string, string);
    void display();

    friend class TM;

private:
    int num;
    int step;
    string nowState;
    vector<deque<int>> Index;
    vector<int> headIndex;
    vector<deque<char>> tapes;
};

#endif // ID_H