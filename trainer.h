class Trainer
{
public:
    void open_episode()
    {
        episode.clear();
    }
    void add_state(state s)
    {
        episode.push_back(s);
    }
    void close_episode()
    {
        //train
    }
    int get_value(state s)
    {
        //v(s)
        return 0;
    }
private:
    vector<state> episode;
    // some data structure to save the weights
};