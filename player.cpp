#include "player.h"
#include "state.h"

void Player::init(state *s){
    //set the basic value
    this->pon.setValue(341, 2256, 10);
    this->naya.setValue(502, 1857, 8);
    this->dica.setValue(693, 3119, 8);
    //Set up the characters' diamond buff
    this->pon.setDiamondBuff(255, 511, 1023);
    this->naya.setDiamondBuff(301, 602, 1255);
    this->dica.setDiamondBuff(311, 1039, 1559);
    this->game = s;
}
void Player::setSelectedIndex(int index){
    this->selectedCharacterIndex = index;
}
void Player::pon_attack(int diamond)
{
    //Select an enemy to attack
    if(diamond != 1){
        int n = -1;
        printf("Select an enemy for pon to attack: ");
        scanf("%d" , &n);
        this->game->setEnemySelectedIndex(n);
    }
    float atk_value = this->pon.attack(diamond);
    //one diamond . minus harm
    if(diamond == 1){
        this->game->enemyHurtFirst(atk_value);
        this->pon.addMinusHarm(3);
    }
    else{
        this->game->enemyHurtSelected(atk_value);
    }    
}
void Player::naya_attack(int diamond)
{
    //Select an enemy to attack
    int n = -1;
    printf("Select an enemy for naya to attack: ");
    scanf("%d" , &n);
    this->game->setEnemySelectedIndex(n);
    //Attack the enemy
    float atk_value = this->naya.attack(diamond);
    
    //20% will give *2 attack in 2 diamond
    if(diamond == 2){
        if(rand()/(float)RAND_MAX < 0.2)
            atk_value *= 2;
    }

    this->game->enemyHurtSelected(atk_value);
    if(diamond == 1)
        this->game->enemyAddEasyHarmFirst(3);
}
void Player::dica_attack(int diamond)
{
    float atk_value = this->dica.attack(diamond);

    if(diamond==1){
        //Select a character to heal
        int n = -1;
        printf("Select an character (0 for pon, 1 for naya, 2 for dica): ");
        scanf("%d" , &n);
        this->game->setPlayerSelectedIndex(n);
        
        PlayerState *p = getSelectedCharater();
        p->heal(atk_value);
        p->addStrengthen(3);
        
    }
    else if(diamond==2){
        int n = -1;
        printf("Select an enemy for dica to attack:");
        scanf("%d" , &n);
        this->game->setEnemySelectedIndex(n);
        this->game->enemyHurtSelected(atk_value);
    }
    else if(diamond==4){     //choose the one who has the least HP to heal
        int leastHP_id = findLeastHP();
        if(leastHP_id == 0)
            this->pon.heal(atk_value);
        else if(leastHP_id == 1)
            this->naya.heal(atk_value);
        else if(leastHP_id == 2)
            this->dica.heal(atk_value);
    }
}

void Player::pon_recover(int diamond){
    this->pon.recoverDiamond(diamond);
}

void Player::naya_recover(int diamond){
    this->naya.recoverDiamond(diamond);
}

void Player::dica_recover(int diamond){
    this->dica.recoverDiamond(diamond);
}

void Player::get_hurt(int index, float hurt)
{
    if(index == 0)
        this->pon.getDamage(hurt);
    else if(index == 1)
        this->naya.getDamage(hurt);
    else
        this->dica.getDamage(hurt);
    checkSelectedCharacterState();
}

void Player::get_hurt_first(float hurt){
    get_hurt(getFirstCharacterIndex(), hurt);
}

void Player::get_hurt_selected(float hurt){
    get_hurt(selectedCharacterIndex, hurt);
}

void Player::get_hurt_less(float hurt){
    get_hurt(findLeastHP(), hurt);
}

void Player::get_hurt_index(int index, float hurt){
    get_hurt(index, hurt);
}

void Player::get_hurt_all(float hurt)
{
    if(!this->pon.isDead())
        this->pon.getDamage(hurt);
    if(!this->naya.isDead())
        this->naya.getDamage(hurt);
    if(!this->dica.isDead())
        this->dica.getDamage(hurt);
    checkSelectedCharacterState();
}

bool Player::player_dead(){
    if(this->pon.isDead() && this->naya.isDead() && this->dica.isDead())
        return true;
    return false;
}

void Player::update(){
    this->pon.update();
    this->naya.update();
    this->dica.update();
}

void Player::print()
{
    if(this->selectedCharacterIndex == 0)
        printf("*");
    printf("PON: HP %f, ATK %f, Recover Diamond: %d\n", this->pon.getHP(), this->pon.getATK(), this->pon.getDiamondAount());
    if(this->selectedCharacterIndex == 1)
        printf("*");
    printf("NAYA: HP %f, ATK %f, Recover Diamond: %d\n", this->naya.getHP(), this->naya.getATK(), this->naya.getDiamondAount());
    if(this->selectedCharacterIndex == 2)
        printf("*");
    printf("DICA: HP %f, ATK %f, Recover Diamond: %d\n", this->dica.getHP(), this->dica.getATK(), this->dica.getDiamondAount());
    puts("--------");
}

int Player::getFirstCharacterIndex(){

    if(!this->pon.isDead())
        return 0;
    if(!this->naya.isDead())
        return 1;
    if(!this->dica.isDead())
        return 2;
    return -1;
}

PlayerState* Player::getFirstCharacter(){
    if(!this->pon.isDead())
        return &pon;
    if(!this->naya.isDead())
        return &naya;
    if(!this->dica.isDead())
        return &dica;
    return NULL;
}

PlayerState* Player::getSelectedCharater(){
    if(this->selectedCharacterIndex == 0){
        return &pon;
    }
    else if (this->selectedCharacterIndex == 1){
        return &naya;
    }
    else{
        return &dica;
    }
    return NULL;
}

void Player::updateSelectedIndex(){
    this->selectedCharacterIndex = getFirstCharacterIndex();
}

void Player::checkSelectedCharacterState(){
    if(this->selectedCharacterIndex == 0){
        if(this->pon.isDead())
            updateSelectedIndex();
    }
    else if (selectedCharacterIndex == 1){
        if(this->naya.isDead())
            updateSelectedIndex();
    }
    else{
        if(this->dica.isDead())
            updateSelectedIndex();
    }
}
int Player::findLeastHP(){
    float leastHP = RAND_MAX;
    int id = -1;
    if(!this->pon.isDead())
        if(this->pon.getHP() < leastHP){
            leastHP = this->pon.getHP();
            id = 0;
        }
    if(!this->naya.isDead())
        if(this->naya.getHP() < leastHP){
            leastHP = this->naya.getHP();
            id = 1;
        }
    if(!this->dica.isDead())
        if(this->dica.getHP() < leastHP){
            leastHP = this->dica.getHP();
            id = 2;
        }
    return id;
}