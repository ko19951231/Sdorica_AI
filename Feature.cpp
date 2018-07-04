#include"Feature.h"
#include<iostream>
using namespace std;

float Feature::estimate(const simple_state& s){
    int index = generateIndex(s);
    cout << index << endl;
    return weight[index];
}

float Feature::update(const simple_state& s, float u){
    int index = generateIndex(s);
    weight[index] += u;
    return weight[index];
}

int Feature::generateIndex(const simple_state &s){
    int index = 0;
    //Get the purple diamond index
    index = getDiamondIndex(s.daimond, 1) << 13;
    //player's state index
    //we only get player's hp
    int playerIndex = s.p_HP[0] << 4 | s.p_HP[1] << 2 | s.p_HP[2];
    index |= (playerIndex << 9);
    //enemies's state index
    //only get if enemies can recover shield itself
    //enemies is dead, enemies' shield is out.
    int enemiesIndex = 0;
    for(int i = 0 ; i < 3; i++){
        enemiesIndex = enemiesIndex << 3;
        if(s.kind[i] >= 4)
            enemiesIndex |= (1 << 2);
        if(s.e_HP[i] > 0)
            enemiesIndex |= (1 << 1);
        if(s.shield[i] > 0)
            enemiesIndex |= 1;
    }
    index |= enemiesIndex;
    return index;
}

int Feature::getDiamondIndex(const int diamond[2][7], int color){
    //diamond: 0 for yellow, 1 for purple, 2 for white
    //we choose only one color to reduce the memory
    int index = 0;
    /* index:
      0  1  2  3  4  5  6
      7  8  9 10 11 12 13 */
    for(int i = 1 ; i >= 0; i--)
        for(int j = 6 ; j >= 0 ; j--){
            index = index << 1;
            if(diamond[i][j] == color)
                index |= 1;
        } 
    return index;
}

