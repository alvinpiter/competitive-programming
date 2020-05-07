#include<bits/stdc++.h>
using namespace std;

/*
Categorize cells into two classes:
* Border cell
* Non-border cell

Notice that non-border cells must be dry land.
At least 1 border (but not corner) cell must be dry land.

Corner cases to handle (there must be at least 1 dry land in each row/column):
* Grid 1 * C
* Grid R * 1
* Grid 2 * C
* Grid R * 2
*/

int R, C, answer;
char grid[503][503];

int main() {
    cin >> R >> C;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> grid[i][j];
        }
    }

    answer = 0;

    if (R <= 2) {
        for (int j = 2; j < C; j++) {
            bool exist = false;
            if (grid[1][j] == '#') exist = true;
            if (R == 2 && grid[2][j] == '#') exist = true;

            if (!exist)
                answer += 1;
        }
    } else if (C <= 2) {
        for (int i = 2; i < R; i++) {
            bool exist = false;
            if (grid[i][1] == '#') exist = true;
            if (C == 2 && grid[i][C] == '#') exist = true;

            if (!exist)
                answer += 1;
        }
    } else {
        bool dryLandExistOnBorder = false;
        for (int j = 2; j < C; j++) {
            if (grid[1][j] == '#' || grid[R][j] == '#')
                dryLandExistOnBorder = true;
        }

        for (int i = 2; i < R; i++) {
            if (grid[i][1] == '#' || grid[i][C] == '#')
                dryLandExistOnBorder = true;
        }

        if (!dryLandExistOnBorder)
            answer += 1;

        for (int i = 2; i < R; i++) {
            for (int j = 2; j < C; j++) {
                if (grid[i][j] != '#')
                    answer += 1;
            }
        }
    }

    cout << answer << endl;
}
