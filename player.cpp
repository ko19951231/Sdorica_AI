#include "player.h"
#include "state.h"

void Player::init(state *s){
    //set the basic value
    pon.setValue(47, 310);
    naya.setValue(61, 225);
    dica.setValue(56, 253);
    //Set up the characters' diamond buff
    pon.setDiamondBuff(1.41, 2.83, 5.67);
    naya.setDiamondBuff(1.58, 3.16, 6.6);
    dica.setDiamondBuff(2.07, 2.91, 10.37);
    game = s;
}
float Player::pon_attack(int daimond)
{
    float atk_value = pon.attack(daimond);
    //one diamond . minus harm
    if(daimond == 1)
        pon.addMinusHarm(3);
    return atk_value;
}
float Player::naya_attack(int daimond)
{
    float atk_value = naya.attack(daimond);
    if(daimond == 1)
        game->enemyAddEasyHarmFirst(3);
    return atk_value;
}
float Player::dica_attack(int daimond)
{
    float atk_value = dica.attack(daimond);
        
    if(daimond==1){
        pon.heal(atk_value);
        pon.addStrengthen(3);
        return 0;
    }
    else if(daimond==2){
        return atk_value;
    }
    else if(daimond==4){     //choose the one who has the least HP to heal
        float HP_pon = pon.getHP();
        float HP_naya = naya.getHP();
        float HP_dica = dica.getHP();
        if(HP_pon<HP_naya&&HP_pon<HP_dica) pon.heal(atk_value);
        else if(HP_naya<HP_pon&&HP_naya<HP_dica) naya.heal(atk_value);
        else if(HP_dica<HP_pon&&HP_dica<HP_naya) dica.heal(atk_value);
        return 0;
    }
}
void Player::get_hurt_all(float hurt)
{
    pon.getDamage(hurt);
    naya.getDamage(hurt);
    dica.getDamage(hurt);
}
void Player::get_hurt_first(float hurt)
{
    if(!pon.isDead())
        pon.getDamage(hurt);
    else if(!naya.isDead())
        naya.getDamage(hurt);
    else
        dica.getDamage(hurt);
}
void Player::update(){
    pon.update();
    naya.update();
    dica.update();
}
void Player::print()
{
    printf("PON: HP %f, ATK %f\n", pon.getHP(), pon.getATK());
    printf("NAYA: HP %f, ATK %f\n", naya.getHP(), naya.getATK());
    printf("DICA: HP %f, ATK %f\n", dica.getHP(), dica.getATK());
    puts("--------");
}
