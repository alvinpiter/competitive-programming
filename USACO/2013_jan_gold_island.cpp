#include<bits/stdc++.h>
using namespace std;
#define INF 1000000
#define MAXN 15
#define MAXR 50

int R, C, numCC, ccId[MAXR + 3][MAXR + 3], distCC[MAXN + 3][MAXN + 3], dp[(1 << MAXN) + 3][MAXN + 3];
char grid[MAXR + 3][MAXR + 3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void DFS(int r, int c, int id) {
    ccId[r][c] = id;
    for (int dir = 0; dir < 4; dir++) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        if (nr >= 1 && nr <= R && nc >= 1 && nc <= C && grid[nr][nc] == 'X' && ccId[nr][nc] == 0) {
            DFS(nr, nc, id);
        }
    }
}

void countCC() {
    memset(ccId, 0, sizeof(ccId));

    numCC = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (grid[i][j] == 'X' && ccId[i][j] == 0) {
                numCC += 1;
                DFS(i, j, numCC);
            }
        }
    }
}

void calculateCCDistance() {
    for (int i = 1; i <= numCC; i++) {
        for (int j = 1; j <= numCC; j++) {
            distCC[i][j] = INF;
        }
    }

    for (int current = 1; current <= numCC; current++) {
        int dist[MAXR + 3][MAXR + 3];
        deque<int> qr, qc;

        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                dist[i][j] = INF;

                if (ccId[i][j] == current) {
                    dist[i][j] = 0;
                    qr.push_back(i);
                    qc.push_back(j);
                }
            }
        }

        while (!qr.empty()) {
            int ur = qr.front(); qr.pop_front();
            int uc = qc.front(); qc.pop_front();
            for (int dir = 0; dir < 4; dir++) {
                int nr = ur + dr[dir];
                int nc = uc + dc[dir];

                if (nr >= 1 && nr <= R && nc >= 1 && nc <= C && grid[nr][nc] != '.' && dist[nr][nc] == INF) {
                    int cost = (grid[nr][nc] == 'S' ? 1 : 0);
                    dist[nr][nc] = dist[ur][uc] + cost;

                    if (cost == 0) {
                        qr.push_front(nr);
                        qc.push_front(nc);
                    } else {
                        qr.push_back(nr);
                        qc.push_back(nc);
                    }
                }
            }
        }

        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                if (ccId[i][j] != 0) {
                    int d = min(dist[i][j], distCC[current][ccId[i][j]]);
                    distCC[current][ccId[i][j]] = d;
                    distCC[ccId[i][j]][current] = d;
                }
            }
        }
    }
}

//Min cost to visit all islands in mask and ending at last
int solve(int mask, int last) {
    if ((mask ^ (1 << last)) == 0)
        return 0;

    if (dp[mask][last] != -1)
        return dp[mask][last];

    int best = INF;
    for (int i = 0; i < numCC; i++) {
        if (mask & (1 << i) && i != last) {
            best = min(best, distCC[i + 1][last + 1] + solve(mask ^ (1 << last), i));
        }
    }

    return dp[mask][last] = best;
}

int main() {
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);

    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++)
            cin >> grid[i][j];
    }

    countCC();
    calculateCCDistance();

    memset(dp, -1, sizeof(dp));

    int answer = INF;
    for (int last = 0; last < numCC; last++)
        answer = min(answer, solve((1 << numCC) - 1, last));

    cout << answer << endl;
}
