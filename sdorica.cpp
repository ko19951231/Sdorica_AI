#include<cstdio>
#include<cstdlib>
#include<vector>
#include<time.h>

using namespace std;

#include "state.h"
#include "trainer.h"

int main()
{
    srand(time(NULL));
    state game;
    Trainer trainer; 
    int num_episode = 1;
    for(int i = 0 ; i < num_episode ; i++){
        int total_point = 0;
        game.init();
        trainer.open_episode();
        while(1){
            //The enemy attack first
            bool gameOver = game.enemy_move();
            if(gameOver) break;

            game.print();
            //Input the sliding value
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
            //The reward will be returned after one round
            int point = game.player_move(r, c);
            game.print();
            trainer.add_state(game);
            
            //debug
            if(point > 0)
                printf("Reward: %d\tTotal Reward: %d\n", point, total_point);
            
            //Add the reward
            total_point += point;
            //The 5th state will give 100 for bonus
            //So if the point > 100, means that an episode is over
            if(point > 100) break;

            //update the CD and "state" after one round
            //don't update when in new stage
            if(point != 0)
                game.update();
        }
        trainer.close_episode();
    }
    
}