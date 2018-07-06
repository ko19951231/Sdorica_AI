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
    float getDamage(float damage);
    //Recover hp
    void heal(float hp);
    //Recover shield
    void addShield(float s);
    //Buff add or no
    void addMinusHarm(int round);
    void addEasyHarm(int round);
    void addStrengthen(int round);
    //recove CD value
    void recoverCD();
    //update value and CD after one round
    void update();
    //get value
    float getHP(){return this->HP;}
    float getATK(){return this->ATK;}
    float getShield(){return this->shield;}
    int getCD(){return this->CD;}
    int getKind(){return this->kind;}
    int getSimplifiedHP(int interval){return this->HP>0?((int)(interval*(float)(this->HP-1)/(float)(this->MAX_HP))):0;}
    int getSimplifiedShiled(int interval){return this->shield>0?((int)(interval*(float)(this->shield-1)/(float)(this->MAX_HP))):0;}
    //set value
    void setEnemy(int k);
    bool isDead(){return this->HP <= 0? true:false;}
    //transfer shield
    void setTransferShield(int v);
    void addShieldTransferLevel();
    //parameter function
    void setKind(int k) {this->kind = k;}
    void setHP(float hp){this->HP = hp;}
    void setATK(float atk){this->ATK = atk;}
    void setShield(float shield){this->shield = shield;}
    float getMAXHP(){return this->MAX_HP;}
    void setMAXHP(float maxHP){this->MAX_HP = maxHP;}
    void setCD(int cd){this->CD = cd;}
    int getCDInterval(){return this->CD_interval;}
    void setCDInterval(int cd_inter){this->CD_interval = cd_inter;}
    int getShieldTransferLevel(){return this->shieldTransfer_level;}
    int setShieldTransferLevel(int s){this->shieldTransfer_level = s;}
    int* getMinusHarm(){return this->minusHarm;}
    void setMinusHarm(int* m){ for(int i = 0 ; i < 3 ; i++) this->minusHarm[i] = m[i];}
    int* getStrengthen(){return this->strengthen;}
    void setStrengthen(int* s){ for(int i = 0 ; i < 3 ; i++) this->strengthen[i] = s[i];}
    int* getEasyHarm(){return this->easyHarm;}
    void setEasyHarm(int* e){ for(int i = 0 ; i < 3 ; i++) this->easyHarm[i] = e[i];}
    int getTransferShield(){return this->transferShield;}
    void assign(const EnemyState &e);
private:
    int kind;   //0: 紅球角鯨 1:草葉巨蚤 2:結草鵝 3:組合偶屍 4:狼人盾兵 5:王國符文師
    float ATK;
    float HP;
    float MAX_HP;
    float shield;
    int CD;
    int CD_interval;
    int shieldTransfer_level;
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