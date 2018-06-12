class Enemy
{
public:
    void init(int s)
    {
        amount = 5;
        //Stage0: mushroom * 5
        //Stage1: mushroom, round, mushroom, mushroom, mushroom.
        //Stage2: mushroom, round, cube, mushroom, mushroom.
        int CD_start = 3;
        if(s >= 3) CD_start+=;
        for(int i = 0 ; i < 5; i++)
            enemies[i].setValue(0, i + CD_start);
        if(s >= 2) enemies[1].setValue(1, CD_start + 1);
        if(s >= 3) enemies[2].setValue(2, CD_start + 2);
    }
    int get_hurt(int index, int hurt)
    {
        bool dead = enemies[index].getDamage(hurt);
        if(dead){
            amount--;
            if(enemies[index].getKind() == 0)
                return 72; // if the mushroom dead, hurt enemies with 72 HP
        }
        return 0;
    }

    void get_hurt_all(int hurt){
        for(int i = 0 ; i < 5; i++){
            int boom = get_hurt(i, hurt);
            if(boom) get_hurt_all(boom);
        }
    }

    void addEasyHarm(int index, int round){
        enemies[index].addEasyHarm(round);
    }

    void print()
    {
        for(int i=0;i<5;i++){
            if(enemies[i].getKind() == 0) printf("Mushroom: HP %d, CD %d\n", enemies[i].getHP(),  enemies[i].getCD());
            else if(enemies[i].getKind() == 1) printf("Round: HP %d, CD %d\n", enemies[i].getHP(),  enemies[i].getCD());
            else if(enemies[i].getKind() == 2) printf("Cube: HP %d, CD %d\n", enemies[i].getHP(),  enemies[i].getCD());
        }
        puts("==============");
    }
private:
    EnemyState enemies[5];
    int stage;  // after all the enemy is dead, a new stage is begin
    int amount; // the amount of the "living" enemy
};