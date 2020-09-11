#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 1000

/*
Categorize cells into two:
* Isolated -> All neighboring cells has different color with it
* Non-isolated -> At least one neighboring cells has same color with it

All non-isolated cells will "spread" and touch isolated cells. Once isolated cell is touched by at least one non-isolated cells, this isolated cell will be non-isolated.

Observation:
Color of non-isolated cells will changes color after each iteration. Like disco lamp, dubz dubz dubz. To know its color at particular iteration, just check the parity of the iteration.

The problems can be simplified to calculate the earliest iteration at which an isolated cell become non-isolated. This can be done with multi-source BFS.
*/

int n, m, t, dist[MAXN + 3][MAXN + 3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
char grid[MAXN + 3][MAXN + 3];

bool inGrid(int r, int c) {
    return (r >= 1 && r <= n && c >= 1 && c <= m);
}

bool isIsolated(int r, int c) {
    for (int dir = 0; dir < 4; dir++) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if (inGrid(nr, nc) && grid[nr][nc] == grid[r][c])
            return false;
    }

    return true;
}

int main() {
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cin >> grid[i][j];
    }

    memset(dist, -1, sizeof(dist));

    queue<pair<int, int> > q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!isIsolated(i, j)) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        auto front = q.front(); q.pop();
        int ur = front.first, uc = front.second;

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir], vc = uc + dc[dir];

            if (inGrid(vr, vc) && dist[vr][vc] == -1) {
                dist[vr][vc] = dist[ur][uc] + 1;
                q.push({vr,  vc});
            }
        }
    }

    for (int i = 1; i <= t; i++) {
        int r, c;
        LL iteration;

        cin >> r >> c >> iteration;

        if (dist[r][c] == -1 || dist[r][c] > iteration)
            cout << grid[r][c] << endl;
        else {
            int parity = (iteration - dist[r][c])%2;
            if (parity == 0)
                cout << grid[r][c] << endl;
            else
                cout << (grid[r][c] == '0' ? '1' : '0') << endl;
        }
    }
}
