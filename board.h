#ifndef BOARD_H
#define BOARD_H
class Board
{
public:
    void init() // generate a new board
    {
        for(int r=0;r<2;r++){
            for(int c=0;c<7;c++){
                //The color of the diamond is randomized initially
                daimond[r][c]=rand()%3;
            }
        }
    }
    int slide(vector<int> r, vector<int> c) // a sequence of points to slide
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
        return color*4+r.size();            // return the color and the number of daimond eliminated
    }
    void pop_up()     // pop up new daimond
    {
        srand(time(NULL));
        for(int r=0;r<2;r++){
            vector<int> new_c;
            for(int c=0;c<7;c++){
                if(daimond[r][c]!=-1) new_c.push_back(daimond[r][c]);
            }
            for(int c=0;c<new_c.size();c++) daimond[r][c]=new_c[c];
            for(int c=new_c.size();c<7;c++) daimond[r][c]=rand()%3;
        }
    }
    void print()
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
    int daimond[2][7];  // 0 for yellow, 1 for purple, 2 for white
};

#endif