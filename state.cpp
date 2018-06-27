#include"state.h"

void state::init()
{
    board.init();
    player.init(this);
    enemy.init(0, this);
}
void state::player_move(vector<int> r, vector<int> c)
{
    // slide on the board to get the color and number of eliminated daimonds
    int daimond=board.slide(r, c);
    int color=daimond/4;
    int count=daimond%4;
    printf("%d %d\n",color, count);
    // get the value of hurt to the enemy
    float hurt = 0;
    if(color==0) hurt=player.pon_attack(count);
    else if(color==1) hurt=player.naya_attack(count);
    else if(color==2) hurt=player.dica_attack(count);
    // hurt the first enemy and see if there are 72 point return with mushroom's dead
    float enemyHurt = enemy.get_hurt_first(hurt);
    printf("e: %f\n", enemyHurt);
    if(enemyHurt != 0) enemy.get_hurt_all(enemyHurt);
    //no more enemies -> go to the next stage
    if(enemy.getAmount() == 0)
        enemy.nextStage();
}
bool state::enemy_move()
{
    enemy.attack();
    board.pop_up();
    if(player.player_dead())
        return true;
    return false;
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