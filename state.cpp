#include"state.h"

void state::init()
{
    this->board.init();
    this->player.init(this);
    this->enemy.init(0, this);
    this->move_amount = 0;
}
int state::player_move(vector<int> r, vector<int> c)
{
    move_amount++;
    // slide on the board to get the color and number of eliminated daimonds
    int color=board.slide(r, c);
    int count= r.size();
    printf("%d %d\n",color, count);
    // get the value of hurt to the enemy
    float hurt = 0;
    if(color==0){
        if(!this->player.pon_isDead()){
            this->player.pon_attack(count);
        }
        else
            this->player.pon_recover(count);
    }
    else if(color==1){
        if(!this->player.naya_isDead()){
            this->player.naya_attack(count);
        }    
        else   
            this->player.naya_recover(count);
    }
    else if(color==2){
        if(!this->player.dica_isDead()){
            this->player.dica_attack(count);
        }    
        else
            this->player.dica_recover(count);
    }
    if(this->enemy.getAmount() == 0){
        int reward = 100 - move_amount;
        bool gameContinue = this->enemy.nextStage();
        if(!gameContinue) reward += 100;
        move_amount = 0;
        return reward;
    }
    return 0;
        
}
bool state::enemy_move()
{
    this->enemy.attack();
    this->board.pop_up();
    if(this->player.player_dead())
        return true;
    return false;
}
void state::update(){
    this->player.update();
    this->enemy.update();
}
void state::print()
{
    this->board.print();
    this->player.print();
    this->enemy.print();
}
void state::setEnemySelectedIndex(int index){
    this->enemy.setSelectedIndex(index);
}
void state::setPlayerSelectedIndex(int index){
    this->player.setSelectedIndex(index);
}
void state::PlayerHurtFirst(float hurt){
    this->player.get_hurt_first(hurt);
}
void state::PlayerHurtAll(float hurt){
    this->player.get_hurt_all(hurt);
}
void state::PlayerHurtSelected(float hurt){
    this->player.get_hurt_selected(hurt);
}
void state::PlayerHurtLess(float hurt){
    this->player.get_hurt_less(hurt);
}
void state::PlayerHurtIndex(int index, float hurt){
    this->player.get_hurt_index(index, hurt);
}   
void state::enemyHurtFirst(float hurt){
    this->enemy.get_hurt_first(hurt);
}
void state::enemyHurtSelected(float hurt){
    this->enemy.get_hurt_selected(hurt);
}
void state::enemyAddEasyHarmFirst(int round){
    this->enemy.addEasyHarmFirst(round);
}
void state::enemyAddEasyHarmSelected(int round){
    this->enemy.addEasyHarmSelected(round);
}
