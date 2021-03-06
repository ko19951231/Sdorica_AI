
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
    float player_move(vector<int> r, vector<int> c, int idx);
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
    float enemyHurtFirst(float hurt);
    float enemyHurtSelected(float hurt);
    void enemyAddEasyHarmFirst(int round);
    void enemyAddEasyHarmSelected(int round);
    void assign(state& s);
    void next_stage();
    bool clear_enemies(){return this->clearEnemies;}
    bool player_dead(){return player.player_dead();}
    bool game_continue(){return this->gameContinue;}
    int get_point(){return this->point;}
    int get_stage(){return this->enemy.getStage();}
    void set_state(simple_state &s);
    vector<tiles> get_available_moves();
    simple_state get_simple_state(int clear_stage);
    Enemy enemy;
private:
    Board board;
    Player player;
    int move_amount;
    bool gameContinue;
    bool clearEnemies;
    int point;
};
#endif