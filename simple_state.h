<<<<<<< HEAD
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
    int move_amount;
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
    float progress;
};

=======
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
    int move_amount;
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
    float reward; //got _ reward and turn to this simple after state

    void set_reward(float v){this->reward = v;}
    float get_reward(){return this->reward;}
};

>>>>>>> 1d2107b3ed918bb97dc7998f51ca1fc9da4e7010
#endif