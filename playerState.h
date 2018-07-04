#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class PlayerState{
public:
    //Constructor
    //actually there's nothing to deal with atk
    PlayerState();
    PlayerState(float atk, float hp, int diamond);
    //Set initial value
    void setValue(float atk, float hp, int diamond);
    void setSkillBuff(float n1, float n2, float n3);
    //Attack enemy
    float attack(int diamond);
    //Get hurt
    bool getDamage(float damage);
    //Recover with hp
    void heal(float hp);
    //Buff
    void addMinusHarm(int round);
    void addEasyHarm(int round);
    void addStrengthen(int round);
    //If the player is dead -> recover with diamond
    void recoverDiamond(int daimond);
    //update buff and CD after one round
    void update();
    //others
    float getHP(){return HP;}
    int getSimplifiedHP(int interval){return this->HP>0?((int)(interval*(this->HP-1)/(this->MAX_HP))):interval;}
    float getATK(){return ATK;}
    int getDiamondAount(){return recover_diamond;}
    bool isDead(){return HP <= 0? true:false;}
    //parameter function
    void setHP(float hp){this->HP = hp;}
    void setATK(float atk){this->ATK = atk;}
    float getShield(){return this->shield;}
    void setShield(float shield){this->shield = shield;}
    float getMAXHP(){return this->MAX_HP;}
    void setMAXHP(float maxHP){this->MAX_HP = maxHP;}
    int* getMinusHarm(){return this->minusHarm;}
    void setMinusHarm(int* m){ for(int i = 0 ; i < 3 ; i++) this->minusHarm[i] = m[i];}
    int* getStrengthen(){return this->strengthen;}
    void setStrengthen(int* s){ for(int i = 0 ; i < 3 ; i++) this->strengthen[i] = s[i];}
    int* getEasyHarm(){return this->easyHarm;}
    void setEasyHarm(int* e){ for(int i = 0 ; i < 3 ; i++) this->easyHarm[i] = e[i];}
    void setDiamondAmount(int d) {this->recover_diamond = d;}
    void assign(const PlayerState &p);
private:
    float ATK;
    float HP;
    float MAX_HP;
    float shield;
    //The percentage depend by the diamond
    //There are actually only 3 kinds of value of the diamond
    float skillBuff[4];
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