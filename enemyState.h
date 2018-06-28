#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

class EnemyState{
public:
    //Constructor
    EnemyState();
    EnemyState(int k, int cd, float atk);
    //Attack player
    float attack();
    //Get damage from player
    bool getDamage(float damage);
    //Recover hp
    void heal(float hp);
    //Buff add or no
    void addMinusHarm(int round);
    void addEasyHarm(int round);
    void addStrengthen(int round);
    //CD value
    void minusCD();
    void recoverCD();
    //update value after one round
    void update();
    //get value
    float getHP(){return HP;}
    float getATK(){return ATK;}
    int getCD(){return CD;}
    int getKind(){return kind;}
    //set value
    void setValue(int k, int cd, float atk);
    bool isDead(){return HP <= 0? true:false;}
private:
    int kind;   // 0 for mushroom, 1 for round, 2 for cube
    float ATK;
    float HP;
    float MAX_HP;
    float shield;
    int CD;
    int CD_interval;
    //Enemy's state
    //minusHarm(減傷), easyHarm(易傷), strengthen(強化) with there rounds (maximum with 3 times of state)
    int minusHarm[3];
    int strengthen[3];
    int easyHarm[3];
    float calculateMinusHarm();
    float calculateEasyHarm();
    float calculateStrengthen();
};

#endif