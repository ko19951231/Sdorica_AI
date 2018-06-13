#ifndef TRAINER_H
#define TRAINER_H

#include<cstdio>
#include<cstdlib>
#include<vector>

using namespace std;
class state;
class Trainer
{
public:
    void open_episode();
    void add_state(state s);
    void close_episode();
    int get_value(state s);
private:
    vector<state> episode;
    // some data structure to save the weights
};

#endif