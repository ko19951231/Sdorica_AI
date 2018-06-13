#include "enemy.h"
#include "state.h"

void Enemy::init(int s, state *st)
{
    stage = s;
    amount = 5;
    game = st;
    //Stage0: mushroom * 5
    //Stage1: mushroom, round, mushroom, mushroom, mushroom.
    //Stage2: mushroom, round, cube, mushroom, mushroom.
    int CD_start = 3;
    if(s >= 3) CD_start++;
    for(int i = 0 ; i < 5; i++)
        enemies[i].setValue(0, i + CD_start);
    if(s >= 2) enemies[1].setValue(1, CD_start + 1);
    if(s >= 3) enemies[2].setValue(2, CD_start + 2);
}

float Enemy::get_hurt_first(float hurt){
    return get_hurt(getFirstIndex(), hurt);
}

float Enemy::get_hurt(int index, float hurt)
{
    //if the enemy is dead, then return
    if(enemies[index].isDead()) return 0;

    bool dead = enemies[index].getDamage(hurt);
    if(dead){
        amount--;
        if(enemies[index].getKind() == 0)
            return 72; // if the mushroom dead, hurt enemies with 72 HP
    }
    return 0;
}

void Enemy::get_hurt_all(float hurt){
    int hurts = 0;
    for(int i = 0 ; i < 5; i++){
        hurts += get_hurt(hurt, i);
    }
    if(hurts > 0) get_hurt_all(hurts);
}

//Add the "easy harm" state to the first enemy
void Enemy::addEasyHarmFirst(int round){
    enemies[getFirstIndex()].addEasyHarm(round);
}

void Enemy::update(){
    for(int i = 0 ; i < 5; i++)
        if(!enemies[i].isDead())
            enemies[i].update();
}

void Enemy::attack(){
    for(int i = 0 ; i < 5; i++){
        //if the enemy's CD is downcounting to 0
        //Add back the CD time and attack
        if(enemies[i].getCD() == 0){
            if(enemies[i].getKind() <= 1){
                game->PlayerHurtFist(enemies[i].attack());
            }
            else{
                game->PlayerHurtAll(enemies[i].attack());
            }
            enemies[i].recoverCD();
        }
    }
}

int Enemy::getAmount(){
    return amount;
}

bool Enemy::nextStage(){
    //no more enemies -> go to the next stage
    if(amount == 0) {
        stage = (stage + 1) % 3 + 1;
        //if the stage comes back to 0, then game over
        if(stage == 1)
            return true;
        init(stage, game);
    }
    return false;
}

int Enemy::getFirstIndex(){
    //Check the "first" enemy
    int index;
    for(index = 0 ; index < 5; index++)
        if(!enemies[index].isDead()) break;
    return index;
}

void Enemy::print()
{
    for(int i=0;i<5;i++){
        if(enemies[i].getKind() == 0) printf("Mushroom: HP %f, CD %d\n", enemies[i].getHP(),  enemies[i].getCD());
        else if(enemies[i].getKind() == 1) printf("Round: HP %f, CD %d\n", enemies[i].getHP(),  enemies[i].getCD());
        else if(enemies[i].getKind() == 2) printf("Cube: HP %f, CD %d\n", enemies[i].getHP(),  enemies[i].getCD());
    }
    puts("==============");
}
