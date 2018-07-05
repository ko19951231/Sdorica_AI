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
    int diamond[2][7];

    //For training
    float estimate_value;
    float reward;

    void set_value(float v) {this->estimate_value = v;}
    float get_value(){return this->estimate_value;}
    void set_reward(float v){this->reward = reward;}
    float get_reward(){return this->reward;}
};

#endif