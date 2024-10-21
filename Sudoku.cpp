#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef long double ld;

const int BoardSize=4;
const int CellSize=2;

int Board[BoardSize][BoardSize];
int Possible_Solutions = 0;

bool check(int ch,int row,int col){
    //check for row
    for(int i=0;i<BoardSize;i++){
        if(i!=col){
            if(Board[row][i]==ch){
                return 0;
            }
        }
    } 

    //check for col
    for(int i=0;i<BoardSize;i++){
        if(i!=row){
            if(Board[i][col]==ch){
                return 0;
            }
        }
    } 

    //check for cell
    int str=(row/CellSize)*CellSize;
    int stc=(row/CellSize)*CellSize;
    for(int dx=0;dx<CellSize;dx++){
        for(int dy=0;dy<CellSize;dy++){
            if(str+dx==row and stc+dy==col) continue;
            if(Board[str+dx][stc+dy]==ch){
                return 0;
            }
        }
    }
    return 1;
}

void solver(int row,int col){
    if(col==BoardSize+1){
        solver(row+1,0);
    }
    if(row==BoardSize){

        Possible_Solutions++;
        cout<<"Solution\n";
        for(int i=0;i<BoardSize;i++){
            for(int j=0;j<BoardSize;j++){
                cout<<Board[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
        return;
    }

    if(Board[row][col]){
       if(check(Board[row][col],row,col)) solver(row,col+1);
       else return;
    }
    else{
        
        for(int ch=1;ch<=BoardSize;ch++){
            if(ch,row,col){
                Board[row][col]=ch;
                solver(row,col+1);
                Board[row][col]=0;
            }
        }

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0); 

    for(int i=0;i<BoardSize;i++){
        for(int j=0;j<BoardSize;j++){
            cin>>Board[i][j];
        }
    }

    solver(0,0);
    return 0;
}
