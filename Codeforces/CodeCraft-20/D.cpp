#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000
#define DOT '.'
#define DEBUG false

int n, x[MAXN + 3][MAXN + 3], y[MAXN + 3][MAXN + 3];
char answer[MAXN + 3][MAXN + 3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

char getDir(int dir) {
    char dirs[] = {'U', 'R', 'D', 'L'};
    return dirs[dir];
}

char getInverseDir(int dir) {
    char inverseDirs[] = {'D', 'L', 'U', 'R'};
    return inverseDirs[dir];
}

bool isInsideGrid(int r, int c) {
    return (r >= 1 && r <= n && c >= 1 && c <= n);
}

void markEndingCells(int curR, int curC, int targetR, int targetC) {
    for (int dir = 0; dir < 4; dir++) {
        int nextR = curR + dr[dir];
        int nextC = curC + dc[dir];

        if (isInsideGrid(nextR, nextC) && x[nextR][nextC] == targetR && y[nextR][nextC] == targetC && answer[nextR][nextC] == DOT) {
            answer[nextR][nextC] = getInverseDir(dir);
            markEndingCells(nextR, nextC, targetR, targetC);
        }
    }
}

void markCycles(int curR, int curC) {
    for (int dir = 0; dir < 4; dir++) {
        int nextR = curR + dr[dir];
        int nextC = curC + dc[dir];

        if (isInsideGrid(nextR, nextC) && x[nextR][nextC] == -1 && answer[nextR][nextC] == DOT) {
            answer[nextR][nextC] = getInverseDir(dir);
            markCycles(nextR, nextC);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            scanf("%d%d", &x[i][j], &y[i][j]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            answer[i][j] = '.';
        }
    }

    //mark ending cells
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i][j] == i && y[i][j] == j) {
                answer[i][j] = 'X';
                markEndingCells(i, j, i, j);
            }
        }
    }

    //construct cycles
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i][j] == -1) {
                for (int dir = 0; dir < 4; dir++) {
                    int nextR = i + dr[dir];
                    int nextC = j + dc[dir];
                    if (isInsideGrid(nextR, nextC) && x[nextR][nextC] == -1 && y[nextR][nextC] == -1 && answer[nextR][nextC] == DOT) {
                        answer[i][j] = getDir(dir);
                        answer[nextR][nextC] = getInverseDir(dir);

                        markCycles(i, j);
                        markCycles(nextR, nextC);
                    }
                }
            }
        }
    }

    if (DEBUG) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                cout << answer[i][j];
            cout << endl;
        }
    }

    bool valid = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (answer[i][j] == '.') {
                valid = false;
            }
        }
    }

    if (valid) {
        printf("VALID\n");
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                printf("%c", answer[i][j]);

            printf("\n");
        }
    } else {
        printf("INVALID\n");
    }
}

/*
Spiral
3
-1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1

Invalid
3
3 3 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1
-1 -1 -1 -1 1 1
*/
