#ifndef PLAYER_H
#define PLAYER_H
#include<cstdio>
#include<cstdlib>
#include "playerState.h"
using namespace std;
class state;
class Player
{
public:
    void init(state *s);
    float pon_attack(int daimond);
    float yana_attack(int daimond);
    float dica_attack(int daimond);
    void get_hurt_all(float hurt);
    void get_hurt_first(float hurt);
    void update();
    void print();
private:
    PlayerState pon;
    PlayerState naya;
    PlayerState dica;
    state *game;
};

#endif