#include "enemyState.h"

EnemyState::EnemyState(){
    //initial states
    for(int i = 0 ; i < 3; i++){
        minusHarm[i] = 0;
        easyHarm[i] = 0;
        strengthen[i] = 0;
    }
}

EnemyState::EnemyState(int k, int cd){
    kind = k;
    CD = cd;
    if(kind == 0){      //mushroom
        HP = MAX_HP = 120;
        CD_interval = 3;
    }
    else if(kind == 1){ //round monster
        HP = MAX_HP =239;
        CD_interval = 4;
    }
    else if(kind == 2){ //cube monster
        HP = MAX_HP =239;
        CD_interval = 3;
    }
    //initial states
    for(int i = 0 ; i < 3; i++){
        minusHarm[i] = 0;
        easyHarm[i] = 0;
        strengthen[i] = 0;
    }
}

void EnemyState::setValue(int k, int cd){
    kind = k;
    CD = cd;
    if(kind == 0){      //mushroom
        HP = MAX_HP =120;
        CD_interval = 3;
    }
    else if(kind == 1){ //round monster
        HP = MAX_HP =239;
        CD_interval = 4;
    }
    else if(kind == 2){ //cube monster
        HP = MAX_HP =239;
        CD_interval = 3;
    }
}

float EnemyState::attack(){
    //If the enemy is dead, return nothing
    if(isDead()) return 0;
    float currentATK = ATK * calculateStrengthen();
    return currentATK;
}

bool EnemyState::getDamage(float damage){
    HP -= damage * calculateMinusHarm() * calculateEasyHarm();
    //if the character is dead, return true, otherwise, false
    if(HP <= 0) return true;
    return false;
}

void EnemyState::heal(float hp){
    HP += hp;
    if(HP > MAX_HP) HP = MAX_HP;
}

void EnemyState::addEasyHarm(int round){
    int i;
    //Add 'round' to the array
    for(i = 0 ; i < 3 ; i++)
        if(easyHarm[i] == 0){
            easyHarm[i] = round;
            break;
        }
    //The array is full, add it to the first one
    if(i == 3)
        easyHarm[0] = round;
}

void EnemyState::addMinusHarm(int round){
    int i;
    //Add 'round' to the array
    for(i = 0 ; i < 3 ; i++)
        if(minusHarm[i] == 0){
            minusHarm[i] = round;
            break;
        }
    //The array is full, add it to the first one
    if(i == 3)
        minusHarm[0] = round;
}

void EnemyState::addStrengthen(int round){
    int i;
    //Add 'round' to the array
    for(i = 0 ; i < 3 ; i++)
        if(strengthen[i] == 0){
            strengthen[i] = round;
            break;
        }
    //The array is full, add it to the first one
    if(i == 3)
        strengthen[0] = round;
}

void EnemyState::update(){
    //update the Enemies's buff state
    //update the CD time
    for(int i = 0; i < 3; i++){
        if(easyHarm[i] > 0) easyHarm[i]--;
        if(minusHarm[i] > 0) minusHarm[i]--;
        if(strengthen[i] > 0) strengthen[i]--;
    }
    if(!isDead()) CD--;
}

void EnemyState::recoverCD(){
    CD = CD_interval;
}

float EnemyState::calculateMinusHarm(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(minusHarm[i] > 0) v *= 0.7;
    return v;
}

float EnemyState::calculateEasyHarm(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(easyHarm[i] > 0) v *= 1.3;
    return v;
}

float EnemyState::calculateStrengthen(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(strengthen[i] > 0) v *= 1.3;
    return v;
}