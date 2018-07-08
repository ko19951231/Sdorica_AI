#include "board.h"

void Board::init() // generate a new board
{
    for(int r=0;r<2;r++){
        for(int c=0;c<7;c++){
            //The color of the daimond is randomized initially
            daimond[r][c]=rand()%3;
        }
    }
}
int Board::slide(vector<int> r, vector<int> c) // a sequence of points to slide
{
    int color=daimond[r[0]][c[0]];
    bool bad=0;
    for(int i=1;i<r.size();i++){
        if(r[i]!=r[i-1]&&c[i]!=c[i-1]) bad=1;
        if(daimond[r[i]][c[i]]!=color) bad=1;
        // maybe other 防呆
    }
    if(r.size()==4&&r[0]==r[1]&&r[0]==r[2]&&r[0]==r[3]) bad=1;
    if(bad) return -1;
    for(int i=0;i<r.size();i++){
        daimond[r[i]][c[i]]=-1;
    }
    //push back the diamond
    for(int r=0;r<2;r++){
        vector<int> new_c;
        for(int c=0;c<7;c++){
            if(daimond[r][c]!=-1) new_c.push_back(daimond[r][c]);
        }
        for(int c=0;c<new_c.size();c++) daimond[r][c]=new_c[c];
        for(int c=new_c.size();c<7;c++) daimond[r][c]=-1;
    }

    return color;            // return the color
}
void Board::pop_up()     // pop up new daimond
{
    for(int r=0;r<2;r++){
        vector<int> new_c;
        for(int c=0;c<7;c++){
            if(daimond[r][c]!=-1) new_c.push_back(daimond[r][c]);
        }
        for(int c=0;c<new_c.size();c++) daimond[r][c]=new_c[c];
        for(int c=new_c.size();c<7;c++) daimond[r][c]=rand()%3;
    }
}
void Board::print()
{
    puts("=========");
    for(int r=0;r<2;r++){
        printf("|");
        for(int c=0;c<7;c++){
            if(daimond[r][c]==0) printf("Y");
            else if(daimond[r][c]==1) printf("P");
            else if(daimond[r][c]==2) printf("W");
            else if(daimond[r][c]==-1) printf("_");
        }
        printf("|\n");
    }
    puts("=========");
}
vector<tiles> Board::get_available_moves()
{
    vector<tiles> v;
    for(int r=0;r<2;r++){
        for(int c=0;c<7;c++){
            tiles one;
            one.r.push_back(r);
            one.c.push_back(c);
            v.push_back(one);
            if(r==0&&daimond[r][c]==daimond[r+1][c]){
                tiles two=one;
                two.r.push_back(r+1);
                two.c.push_back(c);
                v.push_back(two);
            }
            if(c<6&&daimond[r][c]==daimond[r][c+1]){
                tiles two=one;
                two.r.push_back(r);
                two.c.push_back(c+1);
                v.push_back(two);
            }
            if(r==0&&c<6&&daimond[r][c]==daimond[r][c+1]&&daimond[r][c]==daimond[r+1][c]&&daimond[r][c]==daimond[r+1][c+1]){
                tiles four=one;
                four.r.push_back(r);
                four.c.push_back(c+1);
                four.r.push_back(r+1);
                four.c.push_back(c+1);
                four.r.push_back(r+1);
                four.c.push_back(c);
                v.push_back(four);
            }
        }
    }
    return v;
}

void Board::assign(Board& b){
    for(int i = 0 ; i < 2 ; i++)
        for(int j = 0 ; j < 7 ; j++)
            this->daimond[i][j] = b.daimond[i][j];
}

void Board::set_state(simple_state &s){
    for(int i = 0 ; i < 2 ; i++)
        for(int j = 0 ; j < 7 ; j++)
            this->daimond[i][j] = s.diamond[i][j];
}