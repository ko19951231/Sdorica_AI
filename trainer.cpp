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
	feature.update(path[path.size()-1], alpha*error);
	for(int i=path.size()-2;i>=0;i--){
		target=(path[i+1].progress-path[i].progress)+feature.estimate(path[i+1]);
		error=target-feature.estimate(path[i]);
		feature.update(path[i], alpha*error);
	}
}