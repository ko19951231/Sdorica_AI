class Player
{
public:
    void init(){
        ATK_pon=47;
        HP_pon=310;
        ATK_yana=61;
        HP_yana=225;
        ATK_dica=56;
        HP_dica=253;
    }
    int pon_attack(int daimond)
    {
        if(daimond==1){
            return ATK_pon*1.41;
        }
        else if(daimond==2){
            return ATK_pon*2.83;
        }
        else if(daimond==4){
            return ATK_pon*5.67;
        }
        //減傷 not yet
    }
    int yana_attack(int daimond)
    {
        if(daimond==1){
            return ATK_yana*1.58;
        }
        else if(daimond==2){
            return ATK_yana*3.16;
        }
        else if(daimond==4){
            return ATK_yana*6.6;
        }
        //易傷 not yet
    }
    int dica_attack(int daimond)
    {
        if(daimond==1){
            HP_pon+=ATK_dica*2.07;
            return 0;
        }
        else if(daimond==2){
            return ATK_dica*2.91;
        }
        else if(daimond==4){     //choose the one who has the least HP to heal
            if(HP_pon<HP_yana&&HP_pon<HP_dica) HP_pon+=ATK_dica*10.37;
            else if(HP_yana<HP_pon&&HP_yana<HP_dica) HP_yana+=ATK_dica*10.37;
            else if(HP_dica<HP_pon&&HP_dica<HP_yana) HP_dica+=ATK_dica*10.37;
            return 0;
        }
        //強化 not yet
    }
    void get_hurt_all(int hurt)
    {
        HP_pon-=hurt;
        HP_dica-=hurt;
        HP_yana-=hurt;
    }
    void get_hurt_pon(int hurt)
    {
        HP_pon-=hurt;
    }
    void print()
    {
        printf("PON: HP %d, ATK %d\n", HP_pon, ATK_pon);
        printf("YANA: HP %d, ATK %d\n", HP_yana, ATK_yana);
        printf("DICA: HP %d, ATK %d\n", HP_dica, ATK_dica);
        puts("--------");
    }
private:
    int ATK_pon;
    int HP_pon;
    int minus_harm;
    int ATK_yana;
    int HP_yana;
    int add_harm;
    int ATK_dica;
    int HP_dica;
    int strengthen;
};