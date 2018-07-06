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
    float get_hurt(int index, float hurt);
    float get_hurt_first(float hurt);
    float get_hurt_selected(float hurt);
    float get_hurt_all(float hurt);
    //add state buff to enemy
    void addEasyHarmFirst(int round);
    void addEasyHarmSelected(int round);
    //update the enemies state and CD
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
    int getSelectedEnemyIndex();
    void assign(const Enemy &e);
    EnemyState enemies[3];
private:
    int stage;  // after all the enemy is dead, a new stage is begin
    int init_amount; //the amount of the enemy in the stage begining
    int amount; // the amount of the "living" enemy
    int selectedEnemyIndex;
    state *game;
    void updateSelectedIndex();
    void checkSelectedEnemyState();
};
#endif