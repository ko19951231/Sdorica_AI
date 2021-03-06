#include"state.h"
#include<iostream>
using namespace std;

void state::init()
{
    this->board.init();
    this->player.init(this);
    this->enemy.init(0, this);
    this->move_amount = 0;
    this->point = 0;
    this->gameContinue = true;
    this->clearEnemies = false;
}
float state::player_move(vector<int> r, vector<int> c, int idx)
{
    move_amount++;
    // slide on the board to get the color and number of eliminated daimonds
    int color=board.slide(r, c);
    int count= r.size();
    // get the value of hurt to the enemy
    float hurt = 0;
    if(color==0){
        if(!this->player.pon_isDead()){
            hurt = this->player.pon_attack(count, idx);
        }
        else
            this->player.pon_recover(count);
    }
    else if(color==1){
        if(!this->player.naya_isDead()){
            hurt = this->player.naya_attack(count, idx);
        }    
        else   
            this->player.naya_recover(count);
    }
    else if(color==2){
        if(!this->player.dica_isDead()){
            hurt = this->player.dica_attack(count, idx);
        }    
        else
            this->player.dica_recover(count);
    }
    if(this->enemy.getAmount() == 0){
        //All enemies were cleared
        this->clearEnemies = true;
        //calculate the points
        this->point = 100 - move_amount;
        if(this->point < 0) this->point = 0;

        //If it is in 5th stage, then the user can't continue the game
        this->gameContinue = this->enemy.nextStage();
        move_amount = 0;
    }
    else{
        this->clearEnemies = false;
        this->point = 0;
    }

    //Return the formal points
    //return this->point;
    
    //Return the atk value (divided by 100 to prevent overflow)
    return hurt;
}

void state::next_stage(){
    this->enemy.go_next_stage();
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
float state::enemyHurtFirst(float hurt){
    return this->enemy.get_hurt_first(hurt);
}
float state::enemyHurtSelected(float hurt){
    return this->enemy.get_hurt_selected(hurt);
}
void state::enemyAddEasyHarmFirst(int round){
    this->enemy.addEasyHarmFirst(round);
}
void state::enemyAddEasyHarmSelected(int round){
    this->enemy.addEasyHarmSelected(round);
}
vector<tiles> state::get_available_moves(){
    return this->board.get_available_moves();
}
simple_state state::get_simple_state(int clear_stage){
    simple_state ret;
    ret.stage=this->enemy.getStage();
    ret.amount=this->enemy.getAmount();
    ret.selectedEnemyIndex=this->enemy.getSelectedEnemyIndex();
    ret.selectedCharacterIndex=this->player.getSelectedCharaterIndex();
    ret.move_amount = this->move_amount;
    //Enemies data
    for(int i=0;i<3;i++){
        ret.kind[i]=this->enemy.enemies[i].getKind();
        ret.e_HP[i]=(int)this->enemy.enemies[i].getSimplifiedHP(4);
        ret.shield[i]=this->enemy.enemies[i].getSimplifiedShiled(4);
        ret.CD[i]=this->enemy.enemies[i].getCD();
        ret.shieldTransfer_level[i]=this->enemy.enemies[i].getShieldTransferLevel();
        for(int j=0;j<3;j++){
            ret.e_minusHarm[i][j]=*(this->enemy.enemies[i].getMinusHarm()+j);
            ret.e_strengthen[i][j]=*(this->enemy.enemies[i].getStrengthen()+j);
            ret.e_easyHarm[i][j]=*(this->enemy.enemies[i].getEasyHarm()+j);
        }
        ret.transferShield[i]=this->enemy.enemies[i].getTransferShield();
    }
    ret.p_HP[0]=this->player.pon.getSimplifiedHP(4);
    ret.p_HP[1]=this->player.naya.getSimplifiedHP(4);
    ret.p_HP[2]=this->player.dica.getSimplifiedHP(4);
    for(int j=0;j<3;j++){
        ret.p_minusHarm[0][j]=*(this->player.pon.getMinusHarm()+j);
        ret.p_strengthen[0][j]=*(this->player.pon.getStrengthen()+j);
        ret.p_easyHarm[0][j]=*(this->player.pon.getEasyHarm()+j);
    }
    for(int j=0;j<3;j++){
        ret.p_minusHarm[1][j]=*(this->player.naya.getMinusHarm()+j);
        ret.p_strengthen[1][j]=*(this->player.naya.getStrengthen()+j);
        ret.p_easyHarm[1][j]=*(this->player.naya.getEasyHarm()+j);
    }
    for(int j=0;j<3;j++){
        ret.p_minusHarm[2][j]=*(this->player.dica.getMinusHarm()+j);
        ret.p_strengthen[2][j]=*(this->player.dica.getStrengthen()+j);
        ret.p_easyHarm[2][j]=*(this->player.dica.getEasyHarm()+j);
    }
    ret.recover_diamond[0]=this->player.pon.getDiamondAount();
    ret.recover_diamond[1]=this->player.naya.getDiamondAount(); 
    ret.recover_diamond[2]=this->player.dica.getDiamondAount(); 
    for(int r=0;r<2;r++){
        for(int c=0;c<7;c++){
            ret.diamond[r][c]=board.daimond[r][c];
        }
    }
    int num;
    if(clear_stage==0){
        ret.progress=6504;
        num=3;
    }
    else if(clear_stage==1){
        ret.progress=13398;
        num=3;
    }
    else if(clear_stage==2){
        ret.progress=16626;
        num=1;
    }
    else if(clear_stage==3){
        ret.progress=21238;
        num=1;
    }
    else if(clear_stage>=4){
        ret.progress=21238+12002*(clear_stage-3);
        num=2;
    }
    for(int i=0;i<num;i++){
        ret.progress-=this->enemy.enemies[i].getHP();
        ret.progress-=this->enemy.enemies[i].getShield();
    }
    return ret;
}

void state::assign(state& s){
    this->move_amount = s.move_amount;
    this->gameContinue = s.gameContinue;
    this->point = s.point;
    this->clearEnemies = s.clearEnemies;
    this->board.assign(s.board);
    this->player.assign(s.player);
    this->enemy.assign(s.enemy);
}

void state::set_state(simple_state &s){
    this->move_amount = 0;
    this->point = 0;
    this->gameContinue = true;
    this->clearEnemies = false;
    this->board.set_state(s);
    this->player.set_state(s);
    this->enemy.set_state(s);
}