#include"Feature.h"

float Feature::estimate(simple_state& s){
    
    s.weight_Index[0] = getDiamondIndex(s.diamond, 0);
    s.weight_Index[1] = getDiamondIndex(s.diamond, 1);
    s.weight_Index[2] = getDiamondIndex(s.diamond, 2);
    //flip the diamond
    for(int i = 0; i < 7 ; i++){
        int t = s.diamond[0][i];
        s.diamond[0][i] = s.diamond[1][i];
        s.diamond[1][i] = t;
    }
    s.weight_Index[4] = getDiamondIndex(s.diamond, 0);
    s.weight_Index[5] = getDiamondIndex(s.diamond, 1);
    s.weight_Index[6] = getDiamondIndex(s.diamond, 2);
    //flip the diamond back
    for(int i = 0; i < 7 ; i++){
        int t = s.diamond[0][i];
        s.diamond[0][i] = s.diamond[1][i];
        s.diamond[1][i] = t;
    }

    float value = 0;
    for(int i = 0 ; i < 6; i++)
        value += weight[s.weight_Index[i]];

    return value;
}

float Feature::update(simple_state& s, float u){

    float value = 0;
    float u_spilt = u / 6.0;
    for(int i = 0 ; i < 6 ; i++){
        weight[s.weight_Index[i]] += u_spilt;
        value += weight[s.weight_Index[i]];
    }

    return value;
}

int Feature::generateIndex(simple_state &s){
    int index = 0;
    //Get the purple diamond index
    index = getDiamondIndex(s.diamond, 1) << 13;
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

int Feature::generateIndex(simple_state&s, int color){
    int index = 0;
    //Get the specific diamond index
    index = getDiamondIndex(s.diamond, color) << 18;
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

int Feature::getDiamondIndex(int diamond[2][7], int color){
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

