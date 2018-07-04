#ifndef SIMPLE_STATE_H
#define SIMPLE_STATE_H

class simple_state
{
public:
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

    //For training
    int estimate_value;
    int reward;

    void set_value(int v) {this->estimate_value = v;}
    void get_value(){return this->estimate_value;}
    void set_reward(int v){this->reward = reward;}
    void get_reward(){return this->reward;}
};

#endif