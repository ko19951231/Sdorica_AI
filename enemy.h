class Enemy
{
public:
    void init()   // randomly generate 5 monsters
    {
        srand(time(NULL));
        for(int i=0;i<5;i++){
            kind[i]=rand()%3;
            if(kind[i]==0){      //mushroom
                HP[i]=120;
                CD[i]=0;
            }
            else if(kind[i]==1){ //round monster
                HP[i]=239;
                CD[i]=0;
            }
            else if(kind[i]==2){ //cube monster
                HP[i]=239;
                CD[i]=0;
            }
        }
    }
    int get_hurt(int hurt)
    {
        HP[0]-=hurt;
        if(HP[0]<=0&&kind[0]==0) return 72;  // if the first mushroom dead, hurt player with 72 HP
        else return 0;
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
};