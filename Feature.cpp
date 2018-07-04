#include"Feature.h"
#include <iostream>
using namespace std;

float Feature::estimate(const simple_state& s){
    
    int index[2];
    generateIndex(s, index);
    float value = 0;
    for(int i = 0 ; i < 2; i++){
        value += this->weight[index[i]];
    }
    return value;
}

float Feature::update(const simple_state& s, float u){

    float value = 0;
    float u_spilt = u / 2.0;
    int index[2];
    generateIndex(s, index);
    for(int i = 0 ; i < 2 ; i++){
        this->weight[index[i]] += u_spilt;
        value += this->weight[index[i]];
    }

    return value;
}

void Feature::generateIndex(const simple_state &s, int *index){

    index[0] = generateIndex(s, 2, false);
    index[1] = generateIndex(s, 2, true);
}

int Feature::generateIndex(const simple_state&s, int color, bool flip){
    int index = 0;
    //Get the specific diamond index
    index = getDiamondIndex(s.diamond, color, flip) << 14;
    //player's state index
    //we only get player's hp
    int playerIndex = s.p_HP[color];
    index |= (playerIndex << 12);
    //enemies's state index
    //only get if enemies can recover shield itself
    //enemies is dead, enemies' shield is out.
    int enemiesIndex = 0;
    for(int i = 0 ; i < 3; i++){
        enemiesIndex = enemiesIndex << 4;
        if(s.kind[i] >= 4)
            enemiesIndex |= (1 << 3);
        if(s.e_HP[i] > 0)
            enemiesIndex |= (1 << 2);
        if(s.shield[i] > 0)
            enemiesIndex |= (1 << 1);
        if(s.transferShield[i] > 0)
            enemiesIndex |= 1;
    }
    index |= enemiesIndex;
    return index;
}

int Feature::getDiamondIndex(const int diamond[2][7], int color, bool flip){
    //diamond: 0 for yellow, 1 for purple, 2 for white
    //we choose only one color to reduce the memory
    int index = 0;
    /* index:
      0  1  2  3  4  5  6
      7  8  9 10 11 12 13 */
    if(!flip)
        for(int i = 1 ; i >= 0; i--)
            for(int j = 6 ; j >= 0 ; j--){
                index = index << 1;
                if(diamond[i][j] == color)
                    index |= 1;
            }
    else
        for(int i = 0 ; i < 2; i++)
            for(int j = 6 ; j >= 0 ; j--){
                index = index << 1;
                if(diamond[i][j] == color)
                    index |= 1;
            } 
    return index;
}

