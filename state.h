#ifndef STATE_H
#define STATE_H
#include "board.h"
#include "player.h"
#include "enemy.h"
class state
{
public:
    void init()
    {
        board.init();
        player.init(this);
        enemy.init(this);
    }
    bool player_move(vector<int> r, vector<int> c)
    {
        // slide on the board to get the color and number of eliminated daimonds
        int daimond=board.slide(r, c);
        int color=daimond/4;
        int count=daimond%4;
        // get the value of hurt to the enemy
        float hurt;
        if(color==0) hurt=player.pon_attack(count);
        else if(color==1) hurt=player.yana_attack(count);
        else if(color==2) hurt=player.dica_attack(count);
        // hurt the first enemy and see if there are 72 point return with mushroom's dead
        float enemyHurt = enemy.get_hurt_first(hurt);
        if(enemyHurt != 0) enemy.get_hurt_all(enemyHurt);
        //no more enemies -> go to the next stage
        if(enemy.getAmount() == 0)
            return enemy.nextStage();
        return false;
    }
    void enemy_move()
    {
        enemy.attack();
        board.pop_up();
    }
    void update(){
        player.update();
        enemy.update();
    }
    void print()
    {
        board.print();
        player.print();
        enemy.print();
    }
    void PlayerHurtFist(float hurt){
        player.get_hurt_first(hurt);
    }
    void PlayerHurtAll(float hurt){
        player.get_hurt_all(hurt);
    }
    void enemyAddEasyHarmFirst(int round){
        enemy.addEasyHarmFirst(round);
    }
private:
    Board board;
    Player player;
    Enemy enemy;
};
#endif