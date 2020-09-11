#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

int q, n;
int visited[3][MAXN + 3][4];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
char grid[3][MAXN + 3];

bool isType1(char c) {
    return (c == '1' || c == '2');
}

bool isType2(char c) {
    return !isType1(c);
}

void solve(int r, int c, int dir) {
    visited[r][c][dir] = true;

    if (r == 2 && c == n && dir == RIGHT)
        return;

    int nextR = r + dr[dir];
    int nextC = c + dc[dir];

    if (nextR >= 1 && nextR <= 2 && nextC >= 1 && nextC <= n) {
        if (isType1(grid[nextR][nextC])) {
            if (!visited[nextR][nextC][dir])
                solve(nextR, nextC, dir);
        }

        if (isType2(grid[nextR][nextC])) {
            if (dir == UP || dir == DOWN) {
                if (!visited[nextR][nextC][LEFT])
                    solve(nextR, nextC, LEFT);

                if (!visited[nextR][nextC][RIGHT])
                    solve(nextR, nextC, RIGHT);
            } else {
                if (!visited[nextR][nextC][UP])
                    solve(nextR, nextC, UP);

                if (!visited[nextR][nextC][DOWN])
                    solve(nextR, nextC, DOWN);
            }
        }
    }
}

int main() {
    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> n;
        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> grid[i][j];
                for (int dir = 0; dir < 4; dir++)
                    visited[i][j][dir] = false;
            }
        }

        if (isType1(grid[1][1]))
            solve(1, 1, RIGHT);
        else
            solve(1, 1, DOWN);

        if (visited[2][n][RIGHT])
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
