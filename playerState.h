#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class PlayerState{
public:
    PlayerState(float atk, float hp);
    void setDiamondBuff(float n1, float n2, float n3);
    float attack(int diamond);
    bool getDamage(float damage);
    void heal(float hp);
    void addMinusHarm(int round);
    void addEasyHarm(int round);
    void addStrengthen(int round);
    void update();
    float getHP(){return HP;}
    float getATK(){return ATK;}
    bool isDead(){return HP <= 0? true:false;}
private:
    float ATK;
    float HP;
    //The percentage depend by the diamond
    //There are actually only 3 kinds of value of the diamond
    float diamondBuff[4];
    //Player's state
    //minusHarm(減傷), easyHarm(易傷), strengthen(強化) with there rounds (maximum with 3 times of state)
    int minusHarm[3];
    int strengthen[3];
    //易傷 在 character上 此次不會用到 但先留著
    int easyHarm[3];

    float calculateMinusHarm();
    float calculateEasyHarm();
    float calculateStrengthen();
};

PlayerState::PlayerState(float atk, float hp){
    ATK = atk; HP = hp;
    for(int i = 0 ; i < 3; i++){
        minusHarm[i] = 0;
        easyHarm[i] = 0;
        strengthen[i] = 0;
    }
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

#endif