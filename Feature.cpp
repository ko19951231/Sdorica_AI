#include"Feature.h"
#include <iostream>
using namespace std;

float Feature::estimate(const simple_state& s){
    
    float value = 0;
    
    //player's character feature
    int index[2];
    for(int i = 0 ; i < 3; i++){
        generateIndex1(s, i, index);
        value += this->weight[(1 << 22) * i + index[0]];
        value += this->weight[(1 << 22) * i + index[1]];
    }
    //enemies feature
    value += this->weight[(1 << 22) * 3 + generateIndex2(s)];

    return value;
}

float Feature::update(const simple_state& s, float u){

    float value = 0;
    float u_spilt = u / 7.0;
    
    //player's character feature
    int index[2];
    for(int i = 0 ; i < 3; i++){
        generateIndex1(s, i, index);
        this->weight[(1 << 22) * i + index[0]] += u_spilt;
        this->weight[(1 << 22) * i + index[1]] += u_spilt;
        value += this->weight[(1 << 22) * i + index[0]];
        value += this->weight[(1 << 22) * i + index[1]];
    }

    //enemies feature
    int enemies_index = generateIndex2(s);
    this->weight[(1 << 22) * 3 + enemies_index] += u_spilt;
    value += this->weight[(1 << 22) * 3 + enemies_index];

    return value;
}

void Feature::generateIndex1(const simple_state &s, int color, int *index){
    index[0] = generateIndex1(s, color, false);
    index[1] = generateIndex1(s, color, true);
}

int Feature::generateIndex1(const simple_state&s, int color, bool flip){
    
    int index = 0;
    //Get the specific diamond index
    index = getDiamondIndex(s.diamond, color, flip) << 8; 
    //player's state index
    //HP: 2 bit, strengthen: 1 bit, minusHarm: 1 bit, recover: 4 bit
    index |= (s.p_HP[color] << 8);
    //strengthen
    for(int i = 0 ; i < 3 ; i++){
        if(s.p_strengthen[color][i] > 0){
            index |= (1 << 5);
            break;
        }
    }
    //minus harm
    for(int i = 0 ; i < 3 ; i++){
        if(s.p_minusHarm[color][i] > 0){
            index |= (1 << 4);
            break;
        }
    }
    //recover diamond
    index |= s.recover_diamond[color];
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

int Feature::generateIndex2(const simple_state&s){
    //Enemies Index
    //kind : 1 bit, HP: 2 bit, shield: 1 bit, CD: 2 bit, transfer shield: 1bit
    int index = 0;
    for(int i = 0 ; i < 3; i++){
        index = index << 7;
        if(s.kind[i] >= 4)
            index |= (1 << 6);
        index |= (s.e_HP[i] << 4);
        if(s.shield[i] > 0)
            index |= (1 << 3);
        index |= ((s.CD[i] - 1) << 1);
        index |= (s.transferShield[i]);
    }
    return index;
}

