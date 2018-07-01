#ifndef PLAYER_H
#define PLAYER_H
#include<cstdio>
#include<cstdlib>
#include "playerState.h"
using namespace std;
class state;
class Player
{
public:
    void init(state *s);
    void setSelectedIndex(int index);
    void pon_attack(int diamond);
    void naya_attack(int diamond);
    void dica_attack(int diamond);
    void pon_recover(int diamond);
    void naya_recover(int diamond);
    void dica_recover(int diamond);
    void get_hurt(int index, float hurt);
    void get_hurt_selected(float hurt);
    void get_hurt_first(float hurt);
    void get_hurt_all(float hurt);
    void get_hurt_less(float hurt);
    void get_hurt_index(int index, float hurt);
    bool pon_isDead(){ return pon.isDead();}
    bool naya_isDead(){return naya.isDead();}
    bool dica_isDead(){return dica.isDead();}
    bool player_dead();
    void update();
    void print();
    int getSelectedCharaterIndex();

    PlayerState pon;
    PlayerState naya;
    PlayerState dica;    
private:
    state *game;
    int selectedCharacterIndex;
    int getFirstCharacterIndex();
    PlayerState* getFirstCharacter();
    PlayerState* getSelectedCharater();
    void updateSelectedIndex();
    void checkSelectedCharacterState();
    int findLeastHP();
};

#endif