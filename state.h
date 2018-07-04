
#ifndef STATE_H
#define STATE_H
#include<cstdio>
#include<cstdlib>
#include<vector>

#include "board.h"
#include "player.h"
#include "enemy.h"
#include "simple_state.h"
using namespace std;

class state
{
public:
    void init();
    int player_move(vector<int> r, vector<int> c, int idx);
    bool enemy_move();
    void update();
    void print();
    void setEnemySelectedIndex(int index);
    void setPlayerSelectedIndex(int index);
    void PlayerHurtFirst(float hurt);
    void PlayerHurtSelected(float hurt);
    void PlayerHurtAll(float hurt);
    void PlayerHurtLess(float hurt);
    void PlayerHurtIndex(int index, float hurt);
    void enemyHurtFirst(float hurt);
    void enemyHurtSelected(float hurt);
    void enemyAddEasyHarmFirst(int round);
    void enemyAddEasyHarmSelected(int round);
    void assign(const state& s);
    vector<tiles> get_available_moves();
    simple_state get_simple_state();
private:
    Board board;
    Player player;
    Enemy enemy;
    int move_amount;
};
#endif