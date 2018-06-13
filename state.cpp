#include"state.h"

void state::init()
{
    board.init();
    player.init(this);
    enemy.init(1, this);
}
bool state::player_move(vector<int> r, vector<int> c)
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
void state::enemy_move()
{
    enemy.attack();
    board.pop_up();
}
void state::update(){
    player.update();
    enemy.update();
}
void state::print()
{
    board.print();
    player.print();
    enemy.print();
}
void state::PlayerHurtFist(float hurt){
    player.get_hurt_first(hurt);
}
void state::PlayerHurtAll(float hurt){
    player.get_hurt_all(hurt);
}
void state::enemyAddEasyHarmFirst(int round){
    enemy.addEasyHarmFirst(round);
}