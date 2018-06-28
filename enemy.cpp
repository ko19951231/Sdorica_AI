#include "enemy.h"
#include "state.h"

void Enemy::init(int s, state *st)
{
    
    this->stage = s;
    this->game = st;
    /*
    this->amount = 3;
    int CD_start = 3;
    for(int i = 0 ; i < 5; i++)
    this->enemies[i].setValue(0);
    if(s >= 1) this->enemies[1].setValue(1);
    if(s >= 2) this->enemies[2].setValue(2);*/
    this->selectedEnemyIndex = 0;
}
void Enemy::setSelectedIndex(int index){
    this->selectedEnemyIndex = index;
}

void Enemy::get_hurt(int index, float hurt)
{
    //if the enemy is dead, then return
    if(this->enemies[index].isDead()) return ;

    bool dead = this->enemies[index].getDamage(hurt);
    if(dead){
        this->amount--;
        if(enemies[index].getKind() == 0)
            this->get_hurt_all(72);
    }
    checkSelectedEnemyState();
}
void Enemy::get_hurt_first(float hurt){
    get_hurt(getFirstIndex(), hurt);
}
void Enemy::get_hurt_selected(float hurt){
    get_hurt(this->selectedEnemyIndex, hurt);
}
void Enemy::get_hurt_all(float hurt){
    int hurts = 0;
    for(int i = 0 ; i < 5; i++){
        get_hurt(i, hurt);
    }
}

//Add the "easy harm" state to the selected enemy
void Enemy::addEasyHarmSelected(int round){
    this->enemies[selectedEnemyIndex].addEasyHarm(round);
}

//Add the "easy harm" state to the first enemy
void Enemy::addEasyHarmFirst(int round){
    this->enemies[getFirstIndex()].addEasyHarm(round);
}

void Enemy::update(){
    for(int i = 0 ; i < 3; i++)
        if(!this->enemies[i].isDead())
            this->enemies[i].update();
}

void Enemy::attack(){
    for(int i = 0 ; i < 3; i++){
        //if the enemy's CD is downcounting to 0
        //Add back the CD time and attack
        if((this->enemies[i].getCD() == 0)&& !this->enemies[i].isDead()){
            if(this->enemies[i].getKind() <= 1){
                this->game->PlayerHurtFirst(this->enemies[i].attack());
            }
            else{
                this->game->PlayerHurtAll(this->enemies[i].attack());
            }
            this->enemies[i].recoverCD();
        }
    }
}

int Enemy::getAmount(){
    return this->amount;
}

int Enemy::getStage(){
    return this->stage;
}

bool Enemy::nextStage(){
    //no more enemies -> go to the next stage
    if(this->amount == 0) {
        if(this->stage == 4)
            return false;
        this->stage = this->stage + 1;
        init(this->stage, this->game);
        return true;
    }
}

int Enemy::getFirstIndex(){
    //Check the "first" enemy
    int index;
    for(index = 0 ; index < 3; index++)
        if(!this->enemies[index].isDead()) break;
    return index;
}

void Enemy::print()
{
    for(int i=0;i < 3;i++){
        if(this->selectedEnemyIndex == i)
            printf("*");
        if(this->enemies[i].getKind() == 0) printf("Mushroom: HP %f, CD %d\n", this->enemies[i].getHP(),  this->enemies[i].getCD());
        else if(this->enemies[i].getKind() == 1) printf("Round: HP %f, CD %d\n", this->enemies[i].getHP(),  this->enemies[i].getCD());
        else if(this->enemies[i].getKind() == 2) printf("Cube: HP %f, CD %d\n", this->enemies[i].getHP(),  this->enemies[i].getCD());
    }
    puts("==============");
}

void Enemy::updateSelectedIndex(){
    this->selectedEnemyIndex = getFirstIndex();
}

void Enemy::checkSelectedEnemyState(){
    
    if(enemies[selectedEnemyIndex].isDead())
        updateSelectedIndex();
}
