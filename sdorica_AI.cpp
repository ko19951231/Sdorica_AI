#include<cstdio>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<iostream>
#include <fstream>
#include<string>

#include "state.h"
#include "trainer.h"
#include "Feature.h"

using namespace std;

int main()
{
    //Some parameter that often change
    int num_episode = 1000;
    string load_weight = "Models/Sdorica.tar";
    string save_weight = "Models/Sdorica.tar";
    bool load = false;
    bool save = true;
    // set the learning parameters
	float alpha = 0.1;
    //recording data
    string rewardFilename = "Results/Sdorica_Reward_ver1.csv";
    fstream rewardFile;
    rewardFile.open(rewardFilename.c_str(), std::ios::out);
    //Game training setup
    state game;
    state dup_game;
    Trainer trainer;
    Feature feature;
    //load Feature data
    if(load){
        ifstream in;
        in.open(load_weight.c_str(), std::ios::in | std::ios::binary);
        if(in.is_open()){
            cout << "Model is loaded from " << load_weight << endl;
            in >> feature;
        }
        else{
            cout << "Model data not found" << endl;
            exit(1);
        }
    }
    int best_score = 0;
    float avg_score = 0;
    int best_episode = 0;
    int move[4] ={0};
    srand(time(NULL));
    for(int i = 0 ; i < num_episode ; i++){
        int total_point = 0;
        int total_reward = 0;
        int finished = 0;
        int move_amount = 0;
        int clear_stages = 0;
        double remain=0;
        for(int j = 0 ; j < 4 ; j++)
            move[j] = 0;
        game.init();
        dup_game.init();
        trainer.open_episode();
        while(1){
            //The enemy attack first
            bool gameOver = game.enemy_move();
            if(gameOver){
                //game.print();
                if(clear_stages==4){
                    remain+=game.enemy.enemies[0].getShield()+game.enemy.enemies[1].getShield();
                }
                break;
            }
            //Input the sliding value
            vector<tiles> next_move = game.get_available_moves();
            //Select the best slide and object
            int best_slide=0;
            int best_object=0;
            float maximum=-1;
            for(int j=0;j<next_move.size();j++){
                vector<int> r=next_move[j].r;
                vector<int> c=next_move[j].c;
                for(int idx=0;idx<3;idx++){
                    dup_game.assign(game);
                    //reward should be the estimate value + reward
                    float rew=dup_game.player_move(r, c, idx);
                    float est;
                    if(dup_game.player_dead()) est=0;
                    else est=feature.estimate(dup_game.get_simple_state());
                    if ((est + rew) > maximum){
                        best_slide=j;
                        best_object=idx;
                        maximum = est + rew;
                    }
                }
            }
            //Assign to the real one
            vector<int> r=next_move[best_slide].r;
            vector<int> c=next_move[best_slide].c; 


            //Calculate the movement for debugging
            move[r.size() - 1]++; 
            move_amount++;

            //Move the 'real' game
            float rew=game.player_move(r, c, best_object);  
            //Add this state to the trainer
            simple_state s = game.get_simple_state();
            s.set_reward(rew);
            trainer.add_state(s); 
            //Add the reward
            if(game.get_point() >= 0)
                total_point += game.get_point(); 
            total_reward+=rew;

            //If the game cannot be continued, then game over
            //After the 5th stage, the game over
            if(!game.game_continue()) {
                finished = 1;
                break;
            }

            //If the enemies are all dead, go to the next stage
            if(game.clear_enemies()){
                clear_stages++;
                game.next_stage();
            }
            
            //update the CD and "state" after one round
            //don't update when in new stage
            if(game.get_point() == 0)
                game.update();
        }
        cout << "Episode " << i << " Total Point: " << total_point << " Total Reward: " << total_reward << " Move Amount: " << move_amount << " Statge: " << game.get_stage() << " Clear Stages: " << clear_stages << " Remain Shield: " << remain << endl;
        if(clear_stages>4) puts("RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR!!!");
        /*cout << "Movement: ";
        for(int j = 0 ; j < 4 ; j++)
            cout << (j + 1) << ":" << move[j] << " ";
        cout << endl;*/
        if(total_point > best_score){
            best_score = total_point;
            best_episode = i;
        }

        //Testing for dropping the learning rate
        //you can modify it anyway
        if(i < 1000)
            alpha *= 0.8;   
        
        if(i >= (num_episode - 1000))
            avg_score += total_point;
        if((i + 1) % 1000 == 0){
            rewardFile << i << "," << total_point << "," << move_amount << "," << game.get_stage() << "," << finished << endl;
        }    
        trainer.close_episode(feature, alpha);
    }
    rewardFile.close();

    cout << "The best score is: " << best_score << " appear in episode#" << best_episode << endl;
    cout << "The average score is: " << avg_score/1000.0 << endl;
    //Save 
    if(save){
        ofstream out;
        out.open(save_weight.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
        if (out.is_open()) {
			out << feature;
			out.flush();
			out.close();
            cout << "Feature is saved to " << save_weight << endl;
		}
    }
    
}