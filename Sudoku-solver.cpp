#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
using namespace std;
/*
    this program will accept a sudoku board and return its solution if it is possible
    board will have a 0 where there is an empty cell
    this is done by backtracking
    if after some moves it proves to be invalid then it will change its decision at the previous cell
    then try again all the other solutions
*/
int board[9][9];
int subgrid[] = {0,3,6};
bool possible(int row, int col, int num) {
    for(int i=0;i<9;i++) {
        if(board[row][i] == num) return false;
    }
    for(int i=0;i<9;i++) {
        if(board[i][col] == num) return false;
    }
    int sub_grid_x = (row/3), sub_grid_y = (col/3);
    sub_grid_y *= 3, sub_grid_x *= 3;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[sub_grid_x+i][sub_grid_y+j] == num) return false;
        }
    }
    return true;
}
void print() {
    for(int i=0;i<9;i++) {
        if(!(i%3)) cout<<"-------------------------\n";
        for(int j=0;j<9;j++) {
            if(!(j%3)) cout<<"| ";
            cout<<board[i][j]<<" ";
        }
        cout<<"|\n";
    }
    cout<<"-------------------------\n";
}

bool validate() {
    for(int i=0;i<9;i++) {
        set<int> s, s1;
        for(int j=0;j<9;j++) {
            s.insert(board[i][j]);
            s1.insert(board[j][i]);
        }
        if(s.size() < 9 || s1.size() < 9) return false;
    }
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            set<int> s;
            for(int k=subgrid[i];k<subgrid[i]+3;k++) {
                for(int l=subgrid[j];l<subgrid[j]+3;l++) {
                    s.insert(board[k][l]);
                }
            }
            if(s.size() < 9) return false;
        }
    }
    return true;
}

void solve() {
    for(int row=0;row<9;row++) {
        for(int col=0;col<9;col++) {
            if(board[row][col] == 0) {
                for(int num=1;num<=9;num++) {
                    if(possible(row,col,num)) {
                        board[row][col] = num;
                        solve();
                        board[row][col] = 0; // backtrack
                    }
                }
                return;
            }
        }
    }
    if(validate()) {
        print();
        exit(0);
    }
    return;
}

int main() {
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) cin>>board[i][j];
    }
    solve();
    return 0;
}
