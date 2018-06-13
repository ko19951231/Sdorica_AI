#ifndef ENEMY_H
#define ENEMY_H
#include<cstdio>
#include<cstdlib>
#include "enemyState.h"

using namespace std;
class state;

class Enemy
{
public:
    void init(int s, state *st);
    //hurt the first enemy
    float get_hurt_first(float hurt);
    float get_hurt(int index, float hurt);
    void get_hurt_all(float hurt);
    //Add the "easy harm" state to the first enemy
    void addEasyHarmFirst(int round);
    void update();
    void attack();
    int getAmount();
    bool nextStage();
    int getFirstIndex();
    void print();
private:
    EnemyState enemies[5];
    int stage;  // after all the enemy is dead, a new stage is begin
    int amount; // the amount of the "living" enemy
    state *game;
};
#endif