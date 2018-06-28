#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class PlayerState{
public:
    PlayerState();
    PlayerState(float atk, float hp);
    void setValue(float atk, float hp);
    void setDiamondBuff(float n1, float n2, float n3);
    float attack(int diamond);
    bool getDamage(float damage);
    void heal(float hp);
    void addMinusHarm(int round);
    void addEasyHarm(int round);
    void addStrengthen(int round);
    void recoverDiamond(int daimond);
    void update();
    float getHP(){return HP;}
    float getATK(){return ATK;}
    int getDiamondAount(){return recover_diamond;}
    bool isDead(){return HP <= 0? true:false;}
private:
    float ATK;
    float HP;
    float MAX_HP;
    //The percentage depend by the diamond
    //There are actually only 3 kinds of value of the diamond
    float diamondBuff[4];
    //Player's state
    //minusHarm(減傷), easyHarm(易傷), strengthen(強化) with there rounds (maximum with 3 times of state)
    int minusHarm[3];
    int strengthen[3];
    int easyHarm[3];
    //The diamond should be use to make the character alive
    int recover_diamond;
    int RECOVER_DIAMOND_AMOUNT;

    float calculateMinusHarm();
    float calculateEasyHarm();
    float calculateStrengthen();
};


#endif