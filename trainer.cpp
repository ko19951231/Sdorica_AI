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
    float exact = path.back().get_reward();
	cout << "f " << exact << " ";
	for (path.pop_back() /* terminal state */; path.size(); path.pop_back()) {
		simple_state& move = path.back();
		//move.value(): reward + estimate(afterState)
		//exact : rnext + V(s'next)
		float error = exact - (move.get_value() - move.get_reward());
		exact = move.get_reward() + feature.update(move, alpha * error);
	}
	cout << exact << endl;
}