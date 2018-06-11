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
        if(boom) enemy.get_hurt_all(boom);
        //no more enemies -> go to the next stage
        if(enemy.amount == 0) enemy.stage = (enemy.stage + 1) % 3;
    }
    void enemy_move()
    {
        // enemy with the specific index attacks
        // if it's CD isn't 0 ?????????????
        for(int i = 0 ; i < 5; i++){
            if(enemy.CD[i] == 0){
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
            }
            else{
                enemy.CD[i]--;
            }
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