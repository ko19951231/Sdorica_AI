#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

class EnemyState{
public:
    EnemyState();
    EnemyState(int k, int cd);
    float attack();
    bool getDamage(float damage);
    void heal(float hp);
    void addMinusHarm(int round);
    void addEasyHarm(int round);
    void addStrengthen(int round);
    void update();
    void recoverCD();
    float getHP(){return HP;}
    float getATK(){return ATK;}
    int getCD(){return CD;}
    int getKind(){return kind;}
    void setValue(int k, int cd);
    bool isDead(){return HP <= 0? true:false;}
private:
    int kind;   // 0 for mushroom, 1 for round, 2 for cube
    float ATK;
    float HP;
    float MAX_HP;
    int CD;
    int CD_interval;
    //Player's state
    //minusHarm(減傷), easyHarm(易傷), strengthen(強化) with there rounds (maximum with 3 times of state)
    //enemy只會用到easyHarm
    int minusHarm[3];
    int strengthen[3];
    int easyHarm[3];

    float calculateMinusHarm();
    float calculateEasyHarm();
    float calculateStrengthen();
};

#endif