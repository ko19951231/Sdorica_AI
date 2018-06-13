#include "playerState.h"

PlayerState::PlayerState(){
    for(int i = 0 ; i < 3; i++){
        minusHarm[i] = 0;
        easyHarm[i] = 0;
        strengthen[i] = 0;
    }
}

PlayerState::PlayerState(float atk, float hp){
    ATK = atk; HP = hp;
    for(int i = 0 ; i < 3; i++){
        minusHarm[i] = 0;
        easyHarm[i] = 0;
        strengthen[i] = 0;
    }
}

void PlayerState::setValue(float atk, float hp){
    ATK = atk; HP = hp;
}

void PlayerState::setDiamondBuff(float n1, float n2, float n3){
    diamondBuff[0] = n1;
    diamondBuff[1] = n2;
    diamondBuff[2] = 0;
    diamondBuff[3] = n3;
}

float PlayerState::attack(int diamond){
    //If the player is dead, return nothing
    if(isDead()) return 0;

    float currentATK = ATK * calculateStrengthen();
    return currentATK * diamondBuff[diamond];
}

bool PlayerState::getDamage(float damage){
    HP -= damage * calculateMinusHarm() * calculateEasyHarm();
    //if the character is dead, return true, otherwise, false
    if(HP <= 0) return true;
    return false;
}

void PlayerState::heal(float hp){
    HP += hp;
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
