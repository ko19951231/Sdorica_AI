#include<cstdio>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<iostream>
#include <fstream>
#include<string>

#include "state.h"
#include "Feature.h"
#include "simple_state.h"

using namespace std;

simple_state load(string filepath);
vector<int> parse_string(string s, string pattern);

int main()
{
    string input_state_data = "example.txt";
    string load_weight = "Models/Sdorica.tar";
    
    state game;
    state dup_game;
    Feature feature;

/*
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
*/
    //Input the state
    simple_state s = load(input_state_data);
   
   	for(int i = 0 ; i < 3; i++)
   		cout << s.recover_diamond[i] << endl;
    
    for(int i = 0 ; i < s.amount ; i++)
    	cout << s.e_easyHarm[i][0] << endl;

    //Set the state of the game
    game.set_state(s);
    game.print();
    /*
    //Try all the combination to give the suggest answer
    //Input the sliding value
    vector<tiles> next_move = game.get_available_moves();
    //Select the best slide and object
    int best_slide=0;
    int best_object=0;
    int maximum=-1;
    float best_value = 0;
    float best_reward = 0;
    for(int j=0;j<next_move.size();j++){
        vector<int> r=next_move[j].r;
        vector<int> c=next_move[j].c;
        for(int idx=0;idx<3;idx++){
            dup_game.assign(game);
            //reward should be the estimate value + reward
            int rew=dup_game.player_move(r, c, idx);
            if ((!dup_game.player_dead()) && (dup_game.game_continue())) {
                //estimate the value after the movement
                float est = feature.estimate(dup_game.get_simple_state());
                if (((int)est + rew) > maximum){
                    best_slide=j;
                    best_object=idx;
                    maximum = ((int)est + rew);
                    best_reward = rew;
                    best_value = est + rew;
                }             
			} else {
				best_reward = rew;
                best_value = -100;
			}
        }
    }

    cout << "Suggest Slide: " << endl;
    for(int i = 0 ; i < next_move[best_slide].r.size() ; i++){
        for(int j = 0 ; j < next_move[best_slide].c.size(); j++)
            cout << "Row: " << (i + 1) << " Column: " << (j + 1) << endl;
    }
    cout << "Suggest Select Enemy: " << (best_object + 1) << endl;
    */
    return 0;
}

simple_state load(string filepath){
    simple_state s;
    //Open file
    ifstream inputfile;
    inputfile.open(filepath.c_str(), ios::in);
    if(!inputfile.is_open()){
        cerr << "file isn't opened!" << endl;
        exit(1);
    }
    
    string spilt_pattern = " ";
    string text = "";
    vector<int> nums;
    
	//Input stage data
    getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    s.stage = nums[0]; s.amount = nums[1];
    
    //Input board data
    getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    for(int i = 0 ; i < 7 ; i++)
    	s.diamond[0][i] = nums[i];
    getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    for(int i = 0 ; i < 7 ; i++)
    	s.diamond[1][i] = nums[i];

    //Input player's data
	getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    for(int i = 0 ; i < 3; i++)
    	s.p_HP[i] = nums[i + 3];
    	
    getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    for(int i = 0 ; i < 3; i++){
    	s.p_strengthen[i][0] = nums[i];
    	s.p_strengthen[i][1] = 0;
    	s.p_strengthen[i][2] = 0;
    	s.p_minusHarm[i][0] = nums[i + 3];
    	s.p_minusHarm[i][1] = 0;
    	s.p_minusHarm[i][2] = 0;
	}
    	 
    getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    for(int i = 0 ; i < 3; i++)
    	s.recover_diamond[i] = nums[i];
    	
	//default data: easyHarm = 0
	for(int i = 0 ; i < 3; i++){
		s.p_easyHarm[i][0] = s.p_easyHarm[i][1] = s.p_easyHarm[i][2] = 0;
	}
		 
	//Input enemies' data
	getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    for(int i = 0 ; i < s.amount ; i++){
    	s.kind[i] = nums[i];
    	s.e_HP[i] = nums[i + 2];
    	s.shield[i] = nums[i + 4];
	}
	
	getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    for(int i = 0 ; i < s.amount; i++)
		s.CD[i] = nums[i];
	
	getline(inputfile, text);
    nums = parse_string(text, spilt_pattern);
    for(int i = 0 ; i < s.amount ; i++){
    	s.e_easyHarm[i][0] = nums[i];
    	s.e_easyHarm[i][1] = 0;
    	s.e_easyHarm[i][2] = 0;
    	s.transferShield[i] = nums[i + s.amount];
	}
	//default data: shieldTransfer level = 3, easyHarm = strengthen = 0
	for(int i = 0 ; i < s.amount ; i++){
		s.shieldTransfer_level[i] = 3;
		s.e_minusHarm[i][0] = s.e_minusHarm[i][1] = s.e_minusHarm[i][2] = 0;
		s.e_strengthen[i][0] = s.e_strengthen[i][1] = s.e_strengthen[i][2] = 0;
	}
		
    inputfile.close();
    return s;
}


vector<int> parse_string(string s, string pattern){

    vector<int> nums;
    size_t start, found;
    start = 0;
    found = s.find_first_of(pattern);
    while(found != string::npos){
		string t=s.substr(start,found-start);
		nums.push_back(atoi(t.c_str()));
		start=found+1;
		found=s.find_first_of(pattern, found+1);
    }
    if(found==string::npos)
	{
		string t=s.substr(start,found-start);
		nums.push_back(atoi(t.c_str()));
	}

    return nums;

}
