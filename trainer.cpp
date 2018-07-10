#include "trainer.h"
#include "simple_state.h"
#include "Feature.h"
#include<iostream>
using namespace std;

void Trainer::open_episode()
{
    path.clear();
}
void Trainer::add_state(simple_state s)
{
    path.push_back(s);
}
void Trainer::close_episode(Feature& feature, float alpha)
{
    //train
    //Update the value in the vector
	// td 0
	float target=0;
	float error = target-feature.estimate(path[path.size()-1]);
	int first = 1;
	feature.update(path[path.size()-1], alpha*error, first);
	for(int i=path.size()-2;i>=0;i--){
		target=path[i+1].get_reward()+feature.estimate(path[i+1]);
		error=target-feature.estimate(path[i]);
		feature.update(path[i], alpha*error, first);
		first=0;
	}
}