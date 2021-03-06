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
    int num_episode = 50000;
    string load_weight = "Models/Sdorica2.tar";
    string save_weight = "Models/Sdorica2.tar";
    bool load = true;
    bool save = true;
    // set the learning parameters
	float alpha = 0.0005;
    //recording data
    string rewardFilename = "Results/Sdorica_Max_Reward.csv";
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
    int block=1000;
    float avg=0;
    float max=0;
    int cnt=0;
    for(int i = 0 ; i < num_episode ; i++){
        int total_point = 0;
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
                    dup_game.player_move(r, c, idx);  //rew no use
                    float current_progress=dup_game.get_simple_state(clear_stages).progress;
                    float est;
                    if(dup_game.player_dead()) est=0;
                    else est=feature.estimate(dup_game.get_simple_state(clear_stages));
                    if ((est + current_progress) > maximum){
                        best_slide=j;
                        best_object=idx;
                        maximum = est + current_progress;
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
            game.player_move(r, c, best_object);  
            //Add this state to the trainer
            simple_state s = game.get_simple_state(clear_stages);
            trainer.add_state(s); 
            //Add the reward
            if(game.get_point() >= 0)
                total_point += game.get_point(); 

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
        float progress=game.get_simple_state(clear_stages).progress;
        avg += progress;
        if(progress>max){
            max=progress;
        }

        if(clear_stages>4){
            cout << "Episode " << i << " Total Point: " << total_point << " Move Amount: " << move_amount << " Statge: " << game.get_stage() << " Clear Stages: " << clear_stages << " Progress: " << game.get_simple_state(clear_stages).progress << endl;
            cnt++;
        }        
        if(i%block==block-1){
            cout << i/block <<" "<<avg/block << " " << cnt <<endl;
            avg=0;
            max=0;
            cnt=0;
            //if((i/block)%100==0) alpha*=0.7;
        }
        /*cout << "Movement: ";
        for(int j = 0 ; j < 4 ; j++)
            cout << (j + 1) << ":" << move[j] << " ";
        cout << endl;*/
        if(total_point > best_score){
            best_score = total_point;
            best_episode = i;
        }

        if(i >= (num_episode - 1000))
            avg_score += total_point;
        if((i + 1) % 100 == 0){
            rewardFile << (i + 1) << "," << total_point << "," << move_amount << "," << game.get_stage() << endl;
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
