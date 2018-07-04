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
            vector<tiles> next_move = game.get_available_moves();
            int best_slide=0;
            int best_object=0;
            int maximum=0;
            for(int j=0;j<next_move.size();j++){
                vector<int> r=next_move[j].r;
                vector<int> c=next_move[j].c;
                for(int idx=0;idx<3;idx++){
                    state dup_game=game;
                    int rew=dup_game.player_move(r, c, idx);
                    if(rew>maximum){
                        best_slide=j;
                        best_object=idx;
                        maximum=rew;
                    }
                }
            }
            vector<int> r=next_move[best_slide].r;
            vector<int> c=next_move[best_slide].c;
            
            //Return value
            //The reward will be returned after one round
            int point = game.player_move(r, c, best_object);
            game.print();
            trainer.add_state(game);
            
            //Add the reward
            total_point += point;
            
            //debug
            if(point > 0)
                printf("Reward: %d\tTotal Reward: %d\n", point, total_point);
            
            //The 5th state will give 100 for bonus
            //So if the point > 100, means that an episode is over
            if(point > 100) break;

            //update the CD and "state" after one round
            //don't update when in new stage
            if(point == 0)
                game.update();
        }
        trainer.close_episode();
    }
    
}