class Player
{
public:
    void init(){
        //Set up the characters' diamond buff
        pon.setDiamondBuff(1.41, 2.83, 5.67);
        naya.setDiamondBuff(1.58, 3.16, 6.6);
        dica.setDiamondBuff(2.07, 2.91, 10.37);
    }
    float pon_attack(int daimond)
    {
        float atk_value = pon.attack(daimond);
        //one diamond . minus harm
        if(daimond == 1)
            pon.addminusHarm(2);
        return atk_value;
    }
    float yana_attack(int daimond)
    {
        float atk_value = naya.attack(daimond);
        if(daimond == 1)
            //give the enemy "易傷" state
        return atk_value;
    }
    float dica_attack(int daimond)
    {
        float atk_value = dica . attack(daimond);
        
        if(daimond==1){
            HP_pon+=atk_value;
            //強化
            pon.addStrengthen(2);
            return 0;
        }
        else if(daimond==2){
            return atk_value;
        }
        else if(daimond==4){     //choose the one who has the least HP to heal
            if(HP_pon<HP_yana&&HP_pon<HP_dica) pon.heal(atk_value);
            else if(HP_yana<HP_pon&&HP_yana<HP_dica) naya.heal(atk_value);
            else if(HP_dica<HP_pon&&HP_dica<HP_yana) dica.heal(atk_value);
            return 0;
        }
    }
    void get_hurt_all(int hurt)
    {
        pon.get_hurt(hurt);
        naya.get_hurt(hurt);
        dica.get_hurt(hurt);
    }
    void get_hurt_pon(int hurt)
    {
        pon.get_hurt(hurt);
    }
    void update(){
        pon.update();
        naya.update();
        dica.update();
    }
    void print()
    {
        printf("PON: HP %d, ATK %d\n", pon.getHP(), pon.getATK());
        printf("NAYA: HP %d, ATK %d\n", naya.getHP(), naya.getATK());
        printf("DICA: HP %d, ATK %d\n", dica.getHP(), dica.getATK());
        puts("--------");
    }
private:
    PlayerState pon(47, 310);
    PlayerState naya(61, 225);
    PlayerState dica(56, 253);
};