#include<bits/stdc++.h>
using namespace std;
#define MAXLG 20

pair<int, int> getNext(int r, int c, char dir) {
    if (dir == 'R') return {r, c + 1};
    if (dir == 'D') return {r + 1, c};
    if (dir == 'L') return {r, c - 1};
    if (dir == 'U') return {r - 1, c};
}

int main() {
    int t, n, m;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d", &n, &m);

        char color[n + 3][m + 3], direction[n + 3][m + 3];
        for (int i = 0; i < n; i++) {
            scanf("%s", color[i]);
        }

        for (int i = 0; i < n; i++) {
            scanf("%s", direction[i]);
        }

        int nxt[n * m + 3][MAXLG + 3];

        //base case
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                auto neighbor = getNext(i, j, direction[i][j]);
                nxt[i * m + j][0] = (neighbor.first) * m + neighbor.second;
            }
        }

        for (int lg = 1; lg <= MAXLG; lg++) {
            for (int i = 0; i < n * m; i++) {
                nxt[i][lg] = nxt[nxt[i][lg - 1]][lg - 1];
            }
        }

        /*
        Put one robot at each cell and let it move n*m steps (until their moves are "converged").
        The number of occupied position after n*m steps is the answer.
        */

        //stat[i][j] = -1 if cell (i, j) is not occupied, 0 if cell(i, j) is occupied, 1 if cell(i, j) is occupied by at least 1 robot initially at black cell
        int stat[n * m + 3];
        memset(stat, -1, sizeof(stat));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int cur = i * m + j;
                for (int lg = 0; lg <= MAXLG; lg++) {
                    if ((n*m) & (1 << lg)) {
                        cur = nxt[cur][lg];
                    }
                }

                if (stat[cur] == -1)
                    stat[cur] = 0;

                if (color[i][j] == '0')
                    stat[cur] = 1;
            }
        }

        int answer1 = 0, answer2 = 0;
        for (int i = 0; i < n * m; i++) {
            if (stat[i] != -1) {
                answer1 += 1;
                if (stat[i] == 1)
                    answer2 += 1;
            }
        }

        printf("%d %d\n", answer1, answer2);
    }
}
