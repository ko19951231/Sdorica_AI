#ifndef TRAINER_H
#define TRAINER_H

#include<cstdio>
#include<cstdlib>
#include<vector>

using namespace std;
class simple_state;
class Feature;
class Trainer
{
public:
    void open_episode();
    void add_state(simple_state s);
    void close_episode(Feature& feature);
private:
    vector<simple_state> path;
    // some data structure to save the weights
};

#endif