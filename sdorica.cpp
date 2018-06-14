#include<cstdio>
#include<cstdlib>
#include<vector>
#include<time.h>

using namespace std;

#include "state.h"
#include "trainer.h"

int main()
{
    state game;
    Trainer trainer; 
    srand(time(NULL));
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
        //Return value
        //True: the game is over, False: the game isn't over
        bool gameOver = game.player_move(r, c);
        game.print();
        trainer.add_state(game);
        //update the game state
        //including the player's buff cd and enemies' cd
        game.update();
        if(gameOver) break;
        game.enemy_move();
    }
    trainer.close_episode();
}