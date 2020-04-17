#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    char grid[9][9];

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> grid[i][j];
            }
        }

        grid[0][0] = grid[1][0];
        grid[1][3] = grid[2][3];
        grid[2][6] = grid[1][6];

        grid[3][1] = grid[4][1];
        grid[4][4] = grid[5][4];
        grid[5][7] = grid[4][7];

        grid[6][2] = grid[7][2];
        grid[7][5] = grid[8][5];
        grid[8][8] = grid[7][8];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++)
                cout << grid[i][j];

            cout << endl;
        }
    }
}
