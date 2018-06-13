
#ifndef STATE_H
#define STATE_H
#include<cstdio>
#include<cstdlib>
#include<vector>

#include "board.h"
#include "player.h"
#include "enemy.h"
using namespace std;
class state
{
public:
    void init();
    bool player_move(vector<int> r, vector<int> c);
    void enemy_move();
    void update();
    void print();
    void PlayerHurtFist(float hurt);
    void PlayerHurtAll(float hurt);
    void enemyAddEasyHarmFirst(int round);
private:
    Board board;
    Player player;
    Enemy enemy;
};
#endif