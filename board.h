#ifndef BOARD_H
#define BOARD_H

#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;

struct tiles
{
    vector<int> r;
    vector<int> c;
};

class Board
{
public:
    void init();
    int slide(vector<int> r, vector<int> c);
    void pop_up();
    void print();
    vector<tiles> get_available_moves();
    int daimond[2][7];  // 0 for yellow, 1 for purple, 2 for white
    void assign(Board& b);
};

#endif