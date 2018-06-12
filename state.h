class state
{
public:
    void init()
    {
        board.init();
        player.init();
        enemy.init();
    }
    bool player_move(vector<int> r, vector<int> c)
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
        int enemyHurt=enemy.get_hurt(hurt);
        if(enemyHurt != 0) enemy.get_hurt_all(enemyHurt);
        //no more enemies -> go to the next stage
        if(enemy.amount == 0) {
            enemy.stage = (enemy.stage + 1) % 3;
            //if the stage comes back to 0, then game over
            if(enemy.stage == 0)
                return true;
        }
        return false;
    }
    void enemy_move()
    {
        for(int i = 0 ; i < 5; i++){
            //if the enemy's CD is downcounting to 0
            //Add back the CD time and attack
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
    void update(){
        player.update();
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