#include "enemy.h"
#include "state.h"

void Enemy::init(int s, state *st)
{
    this->stage = s;
    this->amount = 5;
    this->game = st;
    //Stage0: mushroom * 5
    //Stage1: mushroom, round, mushroom, mushroom, mushroom.
    //Stage2: mushroom, round, cube, mushroom, mushroom.
    int CD_start = 3;
    if(s >= 2) CD_start++;
    for(int i = 0 ; i < 5; i++)
        this->enemies[i].setValue(0, i + CD_start, 36);
    if(s >= 1) this->enemies[1].setValue(1, CD_start + 1, 72);
    if(s >= 2) this->enemies[2].setValue(2, CD_start + 2, 36);
}
void selectedEnemyIndex(int index){
    this->selectedEnemyIndex = index;
}

void Enemy::get_hurt(int index, float hurt)
{
    //if the enemy is dead, then return
    if(this->enemies[index].isDead()) return 0;

    bool dead = this->enemies[index].getDamage(hurt);
    if(dead){
        this->amount--;
        if(enemies[index].getKind() == 0)
            this->get_hurt_all(72);
            //return 72; // if the mushroom dead, hurt enemies with 72 HP
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
    for(int i = 0 ; i < 5; i++)
        if(!this->enemies[i].isDead())
            this->enemies[i].update();
}

void Enemy::attack(){
    for(int i = 0 ; i < 5; i++){
        //if the enemy's CD is downcounting to 0
        //Add back the CD time and attack
        if((this->enemies[i].getCD() == 0)&& !this->enemies[i].isDead()){
            if(this->enemies[i].getKind() <= 1){
                this->game->PlayerHurtFist(this->enemies[i].attack());
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

void Enemy::nextStage(){
    //no more enemies -> go to the next stage
    if(this->amount == 0) {
        this->stage = (this->stage + 1) % 3;
        init(this->stage, this->game);
    }
}

int Enemy::getFirstIndex(){
    //Check the "first" enemy
    int index;
    for(index = 0 ; index < 5; index++)
        if(!this->enemies[index].isDead()) break;
    return index;
}

void Enemy::print()
{
    for(int i=0;i<5;i++){
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
