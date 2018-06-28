#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

class EnemyState{
public:
    //Constructor
    EnemyState();
    EnemyState(int k);
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
    //recove CD value
    void recoverCD();
    //update value and CD after one round
    void update();
    //get value
    float getHP(){return HP;}
    float getATK(){return ATK;}
    int getCD(){return CD;}
    int getKind(){return kind;}
    //set value
    void setValue(int k);
    bool isDead(){return HP <= 0? true:false;}
    //transfer shield
    void setTransferShield(int v);
private:
    int kind;   //0: 紅球角鯨 1:草葉巨蚤 2:結草鵝 3:組合偶屍 4:狼人盾兵 5:王國符文師
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
    //被攻擊時，每層轉盾獲得總護盾 10% 的護盾，最高 3 層。
    //此次只會有level 3
    int transferShield;
    float calculateMinusHarm();
    float calculateEasyHarm();
    float calculateStrengthen();
    void init();
};

#endif