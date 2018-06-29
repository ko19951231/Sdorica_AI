#ifndef BOARD_H
#define BOARD_H

#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;

class Board
{
public:
    void init();
    int slide(vector<int> r, vector<int> c);
    void pop_up();
    void print();
    int daimond[2][7];  // 0 for yellow, 1 for purple, 2 for white
};

#endif