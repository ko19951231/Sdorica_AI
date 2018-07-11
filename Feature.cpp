#include"Feature.h"
#include <iostream>
using namespace std;

float Feature::estimate(const simple_state& s)
{
    float ret=0;
    int idx=0;
    for(int i=0;i<3;i++){
        idx*=14;
        if(s.recover_diamond[i]>0) idx+=(10-s.recover_diamond[i]);
        else idx+=10+s.p_HP[i];
        idx*=2;
        bool mh=0;
        for(int j=0;j<3;j++){
            if(s.p_minusHarm[i][j]) mh=1;
        }
        if(mh) idx++;
        idx*=2;
        bool st=0;
        for(int j=0;j<3;j++){
            if(s.p_strengthen[i][j]) st=1;
        }
        if(st) idx++;
    }
    ret += this->weight[idx];
    int offset=175616;
    for(int i=0;i<3;i++){
        idx=0;
        idx*=14;
        if(s.recover_diamond[i]>0) idx+=(10-s.recover_diamond[i]);
        else idx+=10+s.p_HP[i];
        idx*=2;
        bool mh=0;
        for(int j=0;j<3;j++){
            if(s.p_minusHarm[i][j]) mh=1;
        }
        if(mh) idx++;
        idx*=2;
        bool st=0;
        for(int j=0;j<3;j++){
            if(s.p_strengthen[i][j]) st=1;
        }
        if(st) idx++;
        for(int r=0;r<2;r++){
            for(int c=0;c<2;c++){
                idx*=2;
                if(s.diamond[r][c]==i) idx++;
            }
        }
        ret += this->weight[idx+offset];
        offset+=917584;
    }
    return ret;
}

float Feature::update(const simple_state& s, float u)
{
    int idx=0;
    for(int i=0;i<3;i++){
        idx*=14;
        if(s.recover_diamond[i]>0) idx+=(10-s.recover_diamond[i]);
        else idx+=10+s.p_HP[i];
        idx*=2;
        bool mh=0;
        for(int j=0;j<3;j++){
            if(s.p_minusHarm[i][j]) mh=1;
        }
        if(mh) idx++;
        idx*=2;
        bool st=0;
        for(int j=0;j<3;j++){
            if(s.p_strengthen[i][j]) st=1;
        }
        if(st) idx++;
    }
    this->weight[idx]+=u;
    int offset=175616;
    for(int i=0;i<3;i++){
        idx=0;
        idx*=14;
        if(s.recover_diamond[i]>0) idx+=(10-s.recover_diamond[i]);
        else idx+=10+s.p_HP[i];
        idx*=2;
        bool mh=0;
        for(int j=0;j<3;j++){
            if(s.p_minusHarm[i][j]) mh=1;
        }
        if(mh) idx++;
        idx*=2;
        bool st=0;
        for(int j=0;j<3;j++){
            if(s.p_strengthen[i][j]) st=1;
        }
        if(st) idx++;
        for(int r=0;r<2;r++){
            for(int c=0;c<2;c++){
                idx*=2;
                if(s.diamond[r][c]==i) idx++;
            }
        }
        this->weight[idx+offset]+=u;
        offset+=917584;
    }
}



