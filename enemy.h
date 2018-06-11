class Enemy
{
public:
    void init(int s)   // randomly generate 5 monsters
    {
        amount = 5;
        //Stage0: mushroom * 5
        //Stage1: mushroom, round, mushroom, mushroom, mushroom.
        //Stage2: mushroom, round, cube, mushroom, mushroom.
        for(int i = 0 ; i < 5; i++)
            kind[i] = 0;
        if(s >= 2) kind[1] = 1;
        if(s >= 3) kind[2] = 2;
        //Assign the initial state  
        for(int i=0;i<5;i++){
            if(kind[i]==0){      //mushroom
                HP[i]=120;
            }
            else if(kind[i]==1){ //round monster
                HP[i]=239;
            }
            else if(kind[i]==2){ //cube monster
                HP[i]=239;
            }
            CD[i] = i + 3;
            if(s >= 3)  CD[i]++;
        }
    }
    int get_hurt(int index, int hurt)
    {
        if(HP[index] > 0){
            HP[index]-=hurt;
            if(HP[index]<=0 && kind[index]==0) {
                amount--;
                return 72;  // if the first mushroom dead, hurt enemies with 72 HP
            }
        }  
        return 0;
    }

    void get_hurt_all(int hurt){
        for(int i = 0 ; i < 5; i++){
            int boom = get_hurt(i, hurt);
            if(boom) get_hurt_all(boom);
        }
    }

    void print()
    {
        for(int i=0;i<5;i++){
            if(kind[i]==0) printf("Mushroom: HP %d, CD %d\n", HP[i], CD[i]);
            else if(kind[i]==1) printf("Round: HP %d, CD %d\n", HP[i], CD[i]);
            else if(kind[i]==2) printf("Cube: HP %d, CD %d\n", HP[i], CD[i]);
        }
        puts("==============");
    }
    int kind[5];  // 0 for mushroom, 1 for round, 2 for cube
    int HP[5];  
    int CD[5];  
    int stage;  // after all the enemy is dead, a new stage is begin
    int amount; // the amount of the "living" enemy
};