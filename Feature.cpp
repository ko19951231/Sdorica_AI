#include"Feature.h"
#include <iostream>
using namespace std;

float Feature::estimate(const simple_state& s)
{
    float ret=0;
    int idx=0;
    this->est_value.clear();
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
    est_value.push_back(this->weight[idx]);
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
            for(int c=0;c<7;c++){
                idx*=2;
                if(s.diamond[r][c]==i) idx++;
            }
        }
        est_value.push_back(this->weight[idx+offset]);
        ret += this->weight[idx+offset];
        offset+=917504;
    }
    for(int i=0;i<3;i++){
        idx=0;
        if(s.e_HP[i]>=0){
            idx*=5;
            idx+=s.kind[i];
            idx*=7;
            if(s.shield[i]>=0){
                idx+=3;
                idx+=s.shield[i];
            }
            else{
                idx+=s.e_HP[i];
            }
            idx*=2;
            if(s.CD[i]>0) idx++;
            idx*=2;
            bool eh=0;
            for(int j=0;j<3;j++){
                if(s.e_easyHarm[i][j]) eh=1;
            }
            if(eh) idx++;
            idx*=2;
            if(s.transferShield[i]) idx++;
            idx++;
        }
        for(int j=0;j<3;j++){
            idx*=5;
            idx+=(s.p_HP[j]+1);
            idx*=2;
            bool mh=0;
            for(int k=0;k<3;k++){
                if(s.p_minusHarm[j][k]) mh=1;
            }
            if(mh) idx++;
        }
        est_value.push_back(this->weight[idx+offset]);
        ret+=weight[idx+offset];
        offset+=281000;
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
            for(int c=0;c<7;c++){
                idx*=2;
                if(s.diamond[r][c]==i) idx++;
            }
        }
        this->weight[idx+offset]+=u;
        offset+=917504;
    }
    for(int i=0;i<3;i++){
        idx=0;
        if(s.e_HP[i]>=0){
            idx*=5;
            idx+=s.kind[i];
            idx*=7;
            if(s.shield[i]>=0){
                idx+=3;
                idx+=s.shield[i];
            }
            else{
                idx+=s.e_HP[i];
            }
            idx*=2;
            if(s.CD[i]>0) idx++;
            idx*=2;
            bool eh=0;
            for(int j=0;j<3;j++){
                if(s.e_easyHarm[i][j]) eh=1;
            }
            if(eh) idx++;
            idx*=2;
            if(s.transferShield[i]) idx++;
            idx++;
        }
        for(int j=0;j<3;j++){
            idx*=5;
            idx+=(s.p_HP[j]+1);
            idx*=2;
            bool mh=0;
            for(int k=0;k<3;k++){
                if(s.p_minusHarm[j][k]) mh=1;
            }
            if(mh) idx++;
        }
        this->weight[idx+offset]+=u;
        offset+=281000;
    }
}



