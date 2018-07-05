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
    int num_episode = 10000;
    string load_weight = "Models/Sdorica.tar";
    string save_weight = "Models/Sdorica.tar";
    bool load = false;
    bool save = true;
    // set the learning parameters
	float alpha = 0.2;
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
    srand(time(NULL));
    for(int i = 0 ; i < num_episode ; i++){
        int total_point = 0;
        int finished = 0;
        int move_amount = 0;
        game.init();
        dup_game.init();
        trainer.open_episode();
        while(1){
            //The enemy attack first
            bool gameOver = game.enemy_move();
            if(gameOver) break;
            //game.print();
            //Input the sliding value
            vector<tiles> next_move = game.get_available_moves();
            //Select the best slide and object
            int best_slide=0;
            int best_object=0;
            int maximum=-1;
            float best_value = 0;
            int best_reward = 0;
            for(int j=0;j<next_move.size();j++){
                vector<int> r=next_move[j].r;
                vector<int> c=next_move[j].c;
                for(int idx=0;idx<3;idx++){
                    dup_game.assign(game);
                    //reward should be the estimate value + reward
                    int rew=dup_game.player_move(r, c, idx);
                    if (!dup_game.player_dead() && (rew < 100)) {
                        //estimate the value after the movement
                        float est = feature.estimate(dup_game.get_simple_state());
                        if (((int)est + rew) >= maximum){
                            if((est + rew) > 0)
                                cout << move_amount << " " << est << " "  << (rew) << endl;
                            best_slide=j;
                            best_object=idx;
                            maximum = rew + est;
                            best_reward = rew;
                            best_value = est;
                        }        
			        } else {
				        best_reward = rew;
                        best_value = -100;
			        }
                }
            }

            //Assign to the real one
            vector<int> r=next_move[best_slide].r;
            vector<int> c=next_move[best_slide].c;   
            //Return value
            //The reward will be returned after one round
            int point = game.player_move(r, c, best_object);  
            simple_state s = game.get_simple_state();
            s.set_value(best_value);
            s.set_reward(best_reward);
            trainer.add_state(s); 
            //game.print(); 
            //Add the reward
            total_point += point;      
            move_amount++;
            //The 5th state will give 100 for bonus
            //So if the point > 100, means that an episode is over
            if(point >= 100) {
                finished = 1;
                break;
            }

            //update the CD and "state" after one round
            //don't update when in new stage
            if(point == 0)
                game.update();
        }
        cout << "Episode " << i << " Total Point: " << total_point << " Move Amount: " << move_amount << " Finished: " << finished << endl;
        if(total_point > best_score)
            best_score = total_point;
        if(i >= (num_episode - 1000))
            avg_score += total_point;
        if(i % 1000 == 0)
            rewardFile << i << "," << total_point << "," << move_amount << "," << finished << endl;
        trainer.close_episode(feature, alpha);
    }
    rewardFile.close();

    cout << "The best score is: " << best_score << endl;
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