#include<cstdio>
#include<cstdlib>
#include<vector>
#include<time.h>

using namespace std;

#include "board.h"
#include "player.h"
#include "enemy.h"
#include "state.h"
#include "trainer.h"

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