
#ifndef STATE_H
#define STATE_H
#include<cstdio>
#include<cstdlib>
#include<vector>

#include "board.h"
#include "player.h"
#include "enemy.h"
using namespace std;
struct simple_state
{
    //from enemy.h
    int stage; 
    int amount;
    int selectedEnemyIndex;
    //from player.h
    int selectedCharacterIndex;
    //from enemyState.h
    int kind[3]; 
    int e_HP[3];
    int shield[3];
    int CD[3];
    int shieldTransfer_level[3];
    int e_minusHarm[3][3];
    int e_strengthen[3][3];
    int e_easyHarm[3][3];
    int transferShield[3];
    //from playerState.h
    int p_HP[3];
    int p_minusHarm[3][3];
    int p_strengthen[3][3];
    int p_easyHarm[3][3];
    int recover_diamond[3];
    //from board.h
    int daimond[2][7];
};

class state
{
public:
    void init();
    int player_move(vector<int> r, vector<int> c);
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
    vector<tiles> get_available_moves();
    simple_state get_simple_state();
private:
    Board board;
    Player player;
    Enemy enemy;
    int move_amount;
};
#endif