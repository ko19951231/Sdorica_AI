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
    void setSelectedIndex(int index);
    //hurt the enemy
    void get_hurt(int index, float hurt);
    void get_hurt_first(float hurt);
    void get_hurt_selected(float hurt);
    void get_hurt_all(float hurt);
    //add state buff to enemy
    void addEasyHarmFirst(int round);
    void addEasyHarmSelected(int round);
    //minus CD value
    void minusCD();
    //update the enemies state
    void update();
    //attack the player
    void attack();
    //Go to next stage
    bool nextStage();
    //others
    int getAmount();
    int getStage();
    int getFirstIndex();
    void print();
private:
    EnemyState enemies[5];
    int stage;  // after all the enemy is dead, a new stage is begin
    int total_amount; //the amount of the enemy in the stage begining
    int amount; // the amount of the "living" enemy
    int selectedEnemyIndex;
    state *game;
    void updateSelectedIndex();
    void checkSelectedEnemyState();
};
#endif