
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
    void player_move(vector<int> r, vector<int> c);
    bool enemy_move();
    void update();
    void print();
    void setEnemySelectedIndex(int index);
    void setPlayerSelectedIndex(int index);
    void PlayerHurtFirst(float hurt);
    void PlayerHurtSelected(float hurt);
    void PlayerHurtAll(float hurt);
    void enemyHurtFirst(float hurt);
    void enemyHurtSelected(float hurt);
    void enemyAddEasyHarmFirst(int round)
private:
    Board board;
    Player player;
    Enemy enemy;
};
#endif