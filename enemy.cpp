#include "enemy.h"
#include "state.h"

void Enemy::init(int s, state *st)
{
    this->stage = s;
    this->game = st;
    if(this->stage == 0){
        this->init_amount = this->amount = 3;
        this->enemies[0].setEnemy(0);
        this->enemies[1].setEnemy(0);
        this->enemies[2].setEnemy(0);
    }
    else if(this->stage == 1){
        this->init_amount = this->amount = 3;
        this->enemies[0].setEnemy(1);
        this->enemies[1].setEnemy(1);
        this->enemies[2].setEnemy(2);
    }
    else if(this->stage == 2){
        this->init_amount = this->amount = 1;
        this->enemies[0].setEnemy(3);
    }
    else if(this->stage == 3){
        this->init_amount = this->amount = 1;
        this->enemies[0].setEnemy(4);
    }
    else if(this->stage == 4){
        this->init_amount = this->amount = 2;
        this->enemies[0].setEnemy(5);
        this->enemies[1].setEnemy(2);
    }

    this->selectedEnemyIndex = 0;
}
void Enemy::setSelectedIndex(int index){
    this->selectedEnemyIndex = index;
}

void Enemy::get_hurt(int index, float hurt)
{
    //if the enemy is dead, then return
    if(this->enemies[index].isDead()) return;

    bool dead = this->enemies[index].getDamage(hurt);
    if(dead){
        this->amount--;
        checkSelectedEnemyState();
    }
}
void Enemy::get_hurt_first(float hurt){
    get_hurt(getFirstIndex(), hurt);
}
void Enemy::get_hurt_selected(float hurt){
    get_hurt(this->selectedEnemyIndex, hurt);
}
void Enemy::get_hurt_all(float hurt){

    for(int i = 0 ; i < init_amount; i++){
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
    for(int i = 0 ; i < init_amount; i++)
        if(!this->enemies[i].isDead())
            this->enemies[i].update();
}

void Enemy::attack(){
    for(int i = 0 ; i < init_amount; i++){
        //if the enemy's CD is downcounting to 0
        //Add back the CD time and attack
        if((this->enemies[i].getCD() == 0)&& !this->enemies[i].isDead()){
            if(this->enemies[i].getKind() == 0){
                float atk = this->enemies[i].attack();
                this->game->PlayerHurtFirst(atk);
            }
            else if(this->enemies[i].getKind() == 1){
                float atk = this->enemies[i].attack();
                this->game->PlayerHurtAll(atk);
            }
            else if(this->enemies[i].getKind() == 2){
                for(int j = 0 ; j < init_amount ; j++){
                    if(!this->enemies[j].isDead())
                        this->enemies[j].addShieldTransferLevel();
                }
            }
            else if(this->enemies[i].getKind() == 3){
                float atk = this->enemies[i].attack();
                this->game->PlayerHurtFirst(atk);
                this->enemies[i].setTransferShield(1);
            }
            else if(this->enemies[i].getKind() == 4){
                float atk = this->enemies[i].attack();
                this->game->PlayerHurtFirst(atk);
                this->enemies[i].addShield(554);
            }
            else if(this->enemies[i].getKind() == 5){
                float atk = this->enemies[i].attack();
                this->game->PlayerHurtLess(atk);
                this->enemies[i].setTransferShield(1);
                this->enemies[i].addShield(350);
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
    for(index = 0 ; index < init_amount; index++)
        if(!this->enemies[index].isDead()) break;
    return index;
}

void Enemy::print()
{
    for(int i = 0;i < init_amount ; i++){
        if(this->selectedEnemyIndex == i)
            printf("*");
        printf("%d: Monster%d: HP %f, Shield %f, CD %d\n", i, this->enemies[i].getKind(), this->enemies[i].getHP(), this->enemies[i].getShield(), this->enemies[i].getCD());
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
