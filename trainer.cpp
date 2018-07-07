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
	simple_state& next_state = path.back();
	float exact = next_state.get_reward();
	//cout << exact << " " << next_state.get_value() << " " << next_state.get_reward() << endl;
	for (path.pop_back(); path.size(); path.pop_back()) {
		simple_state& move = path.back();
		//move.value(): reward + estimate(afterState)
		//exact : rnext + V(s'next)
		//cout << "before " << exact << " " << move.get_value() << " " << move.get_reward() << endl;
		cout << exact << " " ;
		float error = exact - (move.get_value() - move.get_reward());
		exact = move.get_reward() + feature.update(next_state, alpha * error);
		cout <<  move.get_value() << " " << error << " " <<  (exact - move.get_reward()) << endl;
		next_state = move;
		//cout << exact << " " << move.get_value() << " " << move.get_reward() << endl;
		
	}
}