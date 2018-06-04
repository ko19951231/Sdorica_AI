#include<cstdio>
#include<cstdlib>
#include<vector>
#include<time.h>

using namespace std;

class Board
{
public:
    void init() // generate a new board
    {
        srand(time(NULL));
        for(int r=0;r<2;r++){
            for(int c=0;c<7;c++){
                daimond[r][c]=rand()%3;
            }
        }
    }
    int slide(vector<int> r, vector<int> c) // a sequence of points to slide
    {
        int color=daimond[r[0]][c[0]];
        bool bad=0;
        for(int i=1;i<r.size();i++){
            if(r[i]!=r[i-1]&&c[i]!=c[i-1]) bad=1;
            if(daimond[r[i]][c[i]]!=color) bad=1;
            // maybe other 防呆
        }
        if(r.size()==4&&r[0]==r[1]&&r[0]==r[2]&&r[0]==r[3]) bad=1;
        if(bad) return -1;
        for(int i=0;i<r.size();i++){
            daimond[r[i]][c[i]]=-1;
        }
        return color*4+r.size();            // return the color and the number of daimond eliminated
    }
    void pop_up()     // pop up new daimond
    {
        srand(time(NULL));
        for(int r=0;r<2;r++){
            vector<int> new_c;
            for(int c=0;c<7;c++){
                if(daimond[r][c]!=-1) new_c.push_back(daimond[r][c]);
            }
            for(int c=0;c<new_c.size();c++) daimond[r][c]=new_c[c];
            for(int c=new_c.size();c<7;c++) daimond[r][c]=rand()%3;
        }
    }
    void print()
    {
        puts("=========");
        for(int r=0;r<2;r++){
            printf("|");
            for(int c=0;c<7;c++){
                if(daimond[r][c]==0) printf("Y");
                else if(daimond[r][c]==1) printf("P");
                else if(daimond[r][c]==2) printf("W");
                else if(daimond[r][c]==-1) printf("_");
            }
            printf("|\n");
        }
        puts("=========");
    }
    int daimond[2][7];  // 0 for yellow, 1 for purple, 2 for white
};

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

class state
{
public:
    void init()
    {
        board.init();
        player.init();
        enemy.init();
    }
    void player_move(vector<int> r, vector<int> c)
    {
        // slide on the board to get the color and number of eliminated daimonds
        int daimond=board.slide(r, c);
        int color=daimond/4;
        int count=daimond%4;
        // get the value of hurt to the enemy
        int hurt;
        if(color==0) hurt=player.pon_attack(count);
        else if(color==1) hurt=player.yana_attack(count);
        else if(color==2) hurt=player.dica_attack(count);
        // hurt the enemy and see if there are 72 point return with mushroom's dead
        int boom=enemy.get_hurt(hurt);
        if(boom) player.get_hurt_all(boom);
    }
    void enemy_move(int index)
    {
        // enemy with the specific index attacks
        // if it's CD isn't 0 ?????????????
        if(enemy.kind[index]==0){
            enemy.CD[index]+=3;
            player.get_hurt_pon(36);
        }
        else if(enemy.kind[index]==1){
            enemy.CD[index]+=4;
            player.get_hurt_pon(72);
        }
        else if(enemy.kind[index]==2){
            enemy.CD[index]+=3;
            player.get_hurt_all(36);
        }
        board.pop_up();
    }
    void print()
    {
        board.print();
        player.print();
        enemy.print();
    }
private:
    Board board;
    Player player;
    Enemy enemy;
};

class Trainer
{
public:
    void open_episode()
    {
        episode.clear();
    }
    void add_state(state s)
    {
        episode.push_back(s);
    }
    void close_episode()
    {
        //train
    }
    int get_value(state s)
    {
        //v(s)
        return 0;
    }
private:
    vector<state> episode;
    // some data structure to save the weights
}

int main()
{
    state game;
    Trainer trainer; 
    game.init();
    trainer.open_episode();
    while(1){
        game.print();
        int n;
        scanf("%d", &n);
        vector<int> r;
        vector<int> c;
        for(int i=0;i<n;i++){
            int rr, cc;
            scanf("%d %d", &rr, &cc);
            r.push_back(rr);
            c.push_back(cc);
        }
        game.player_move(r, c);
        game.print();
        trainer.add_state(game);
        srand(time(NULL));
        game.enemy_move(rand()%5);
    }
    trainer.close_episode();
}