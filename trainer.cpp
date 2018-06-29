#include "trainer.h"
#include "state.h"

void Trainer::open_episode()
{
    episode.clear();
}
void Trainer::add_state(state s)
{
    episode.push_back(s);
}
void Trainer::close_episode()
{
    //train
}
int Trainer::get_value(state s)
{
    //v(s)
    return 0;
}