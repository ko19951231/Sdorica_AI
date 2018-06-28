#include "enemyState.h"

EnemyState::EnemyState(){
    //initial states
    for(int i = 0 ; i < 3; i++){
        this->minusHarm[i] = 0;
        this->easyHarm[i] = 0;
        this->strengthen[i] = 0;
    }
    this->transferShield = 0;
}

EnemyState::EnemyState(int k){
    this->kind = k;
    init();
}

void EnemyState::setValue(int k){
    this->kind = k;
    init();
}

void EnemyState::init(){
    if(this->kind == 0){      //紅球角鯨
        this->HP = this->MAX_HP = this->shield = 1084;
        this->ATK = 163;
        this->CD = 4;
        this->CD_interval = 3;
        this->shieldTransfer_level = 3;
    }
    else if(this->kind == 1){ //草葉巨蚤
        this->HP = this->MAX_HP = this->shield = 1149;
        this->ATK = 173;
        this->CD = 0;
        this->CD_interval = 4;
        this->shieldTransfer_level = 0;
    }
    else if(this->kind == 2){ //結草鵝
        this->HP = this->MAX_HP = this->shield = 1149;
        this->ATK = 0;
        this->CD = 0;
        this->CD_interval = 3;
        this->shieldTransfer_level = 0;
    }
    else if(this->kind == 3){ //組合偶屍
        this->HP = this->MAX_HP = this->shield = 1614;
        this->ATK = 388;
        this->CD = 1;
        this->CD_interval = 3;
        this->shieldTransfer_level = 3;
    }
    else if(this->kind == 4){ //狼人盾兵
        this->HP = this->MAX_HP = this->shield = 2306;
        this->ATK = 346;
        this->CD = 3;
        this->CD_interval = 3;
        this->shieldTransfer_level = 3;
    }
    else if(this->kind == 5){ //王國符文師
        this->HP = this->MAX_HP = this->shield = 4852;
        this->ATK = 934;
        this->CD = 3;
        this->CD_interval = 3;
        this->shieldTransfer_level = 3;
    }
    //initial states
    for(int i = 0 ; i < 3; i++){
        this->minusHarm[i] = 0;
        this->easyHarm[i] = 0;
        this->strengthen[i] = 0;
    }
    this->transferShield = 0;
}

float EnemyState::attack(){
    //If the enemy is dead, return nothing
    if(isDead()) return 0;
    float currentATK = this->ATK * calculateStrengthen();
    return currentATK;
}

bool EnemyState::getDamage(float damage){
    float totalDamage = damage * calculateMinusHarm() * calculateEasyHarm();
    //shield first
    if(totalDamage > this->shield){
        totalDamage -= this->shield;
        this->shield = 0;
        this->HP -= totalDamage;
    }
    else{
        this->shield -= totalDamage;
    }
    //Tranfer Shield
    if(this->transferShield > 0){
        this->shield += this->MAX_HP * 0.1 * 3;
        if(this->shield > this->MAX_HP)
            this->shield = this->MAX_HP;
    }
    //if the character is dead, return true, otherwise, false
    if(HP <= 0) return true;
    return false;
}

void EnemyState::heal(float hp){
    this->HP += hp;
    if(this->HP > this->MAX_HP)
        this->HP = this->MAX_HP;
}

void EnemyState::addEasyHarm(int round){
    int i;
    //Add 'round' to the array
    for(i = 0 ; i < 3 ; i++)
        if(this->easyHarm[i] == 0){
            this->easyHarm[i] = round;
            break;
        }
    //The array is full, add it to the first one
    if(i == 3)
        this->easyHarm[0] = round;
}

void EnemyState::addMinusHarm(int round){
    int i;
    //Add 'round' to the array
    for(i = 0 ; i < 3 ; i++)
        if(this->minusHarm[i] == 0){
            this->minusHarm[i] = round;
            break;
        }
    //The array is full, add it to the first one
    if(i == 3)
        this->minusHarm[0] = round;
}

void EnemyState::addStrengthen(int round){
    int i;
    //Add 'round' to the array
    for(i = 0 ; i < 3 ; i++)
        if(this->strengthen[i] == 0){
            this->strengthen[i] = round;
            break;
        }
    //The array is full, add it to the first one
    if(i == 3)
        this->strengthen[0] = round;
}

void EnemyState::addShieldTransferLevel(){
    if(this->shieldTransfer_level >= 3){
        //Not sure
        heal(305);
    }
    else{
        this->shieldTransfer_level++;
    }
}

void EnemyState::recoverCD(){
    this->CD = this->CD_interval;
}

void EnemyState::update(){

    //update the Enemies's buff state
    //update the CD time
    for(int i = 0; i < 3; i++){
        if(this->easyHarm[i] > 0) this->easyHarm[i]--;
        if(this->minusHarm[i] > 0) this->minusHarm[i]--;
        if(this->strengthen[i] > 0) this->strengthen[i]--;
    }
    if(!isDead()) this->CD--;
    
    //recover hp with shield value (盾轉)
    float recover_hp = 0;
    recover_hp = this->shieldTransfer_level * this->shield * 0.3;
    heal(recover_hp);
    
    //recover shield for kind == 4, 5 (狼人盾兵 & 王國符文師)
    if(this->kind == 4){
        this->shield += 554;
        if(this->shield > this->MAX_HP)
            this->shield = this->MAX_HP;
    }
    if(this->kind == 5){
        this->shield += 350;
        if(this->shield > this->MAX_HP)
            this->shield = this->MAX_HP;
    }
    
    //transferShield
    if(transferShield > 0)
        transferShield--;
}

void EnemyState::setTransferShield(int v){
    this->transferShield = v;
}

float EnemyState::calculateMinusHarm(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(this->minusHarm[i] > 0) v *= 0.7;
    return v;
}

float EnemyState::calculateEasyHarm(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(this->easyHarm[i] > 0) v *= 1.3;
    return v;
}

float EnemyState::calculateStrengthen(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(this->strengthen[i] > 0) v *= 1.3;
    return v;
}