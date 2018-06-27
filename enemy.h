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
    //update CD value
    void update();
    //attack the player
    void attack();
    int getAmount();
    void nextStage();
    int getFirstIndex();
    void print();
private:
    EnemyState enemies[5];
    int stage;  // after all the enemy is dead, a new stage is begin
    int amount; // the amount of the "living" enemy
    int selectedEnemyIndex;
    state *game;
    void updateSelectedIndex();
    void checkSelectedEnemyState();
};
#endif