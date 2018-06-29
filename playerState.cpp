#include "playerState.h"
#include<cstdio>

PlayerState::PlayerState(){
    for(int i = 0 ; i < 3; i++){
        minusHarm[i] = 0;
        easyHarm[i] = 0;
        strengthen[i] = 0;
    }
    RECOVER_DIAMOND_AMOUNT = 8;
    recover_diamond = 0;
}

PlayerState::PlayerState(float atk, float hp, int diamond){
    ATK = atk; HP = hp;
    MAX_HP = hp;
    shield = 0;
    for(int i = 0 ; i < 3; i++){
        minusHarm[i] = 0;
        easyHarm[i] = 0;
        strengthen[i] = 0;
    }
    RECOVER_DIAMOND_AMOUNT = diamond;
    recover_diamond = 0;
}

void PlayerState::setValue(float atk, float hp, int diamond){
    ATK = atk; HP = MAX_HP = hp; RECOVER_DIAMOND_AMOUNT = diamond;
}

void PlayerState::setSkillBuff(float n1, float n2, float n3){
    skillBuff[0] = n1;
    skillBuff[1] = n2;
    skillBuff[2] = 0;
    skillBuff[3] = n3;
}

float PlayerState::attack(int diamond){
    //If the player is dead, return nothing
    if(isDead()) return 0;
    float currentATK = ATK * calculateStrengthen();
    return calculateStrengthen() * skillBuff[diamond - 1];
}

bool PlayerState::getDamage(float damage){
    HP -= damage * calculateMinusHarm() * calculateEasyHarm();
    //if the character is dead, return true, otherwise, false
    if(HP <= 0) {
        recover_diamond = RECOVER_DIAMOND_AMOUNT;
        return true;
    }
    return false;
}

void PlayerState::heal(float hp){
    HP += hp;
    if(HP > MAX_HP) HP = MAX_HP;
}

void PlayerState::addEasyHarm(int round){
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

void PlayerState::addMinusHarm(int round){
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

void PlayerState::addStrengthen(int round){
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

void PlayerState::recoverDiamond(int daimond){
    recover_diamond -= daimond;
    if(recover_diamond <= 0){
        HP = MAX_HP / 2.0f;
    }
}

void PlayerState::update(){
    //update the Player's buff state
    for(int i = 0; i < 3; i++){
        if(easyHarm[i] > 0) easyHarm[i]--;
        if(minusHarm[i] > 0) minusHarm[i]--;
        if(strengthen[i] > 0) strengthen[i]--;
    }
}

float PlayerState::calculateMinusHarm(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(minusHarm[i] > 0) v *= 0.7;
    return v;
}

float PlayerState::calculateEasyHarm(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(easyHarm[i] > 0) v *= 1.3;
    return v;
}

float PlayerState::calculateStrengthen(){
    float v = 1.0;
    for(int i = 0 ; i < 3; i++)
        if(strengthen[i] > 0) v *= 1.3;
    return v;
}
