#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 100

/*
Dijkstra on state graph. The state is {current node, step%3}.
*/

struct State {
    int r, c, step;
    State(int _r, int _c, int _step): r(_r), c(_c), step(_step) {}
    bool operator<(State other) const {
        return true;
    }
};

int N, T, grid[MAXN + 3][MAXN + 3], dist[MAXN + 3][MAXN + 3][3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);

    scanf("%d%d", &N, &T);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int s = 0; s < 3; s++) {
                dist[i][j][s] = INF;
            }
        }
    }

    priority_queue<pair<int, State> > pq;
    dist[1][1][0] = 0;
    pq.push({-dist[1][1][0], State(1, 1, 0)});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();

        int r = top.second.r;
        int c = top.second.c;
        int step = top.second.step;

        for (int dir = 0; dir < 4; dir++) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];

            if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
                int cost = T;
                if (step == 2)
                    cost += grid[nr][nc];

                if (dist[nr][nc][(step + 1)%3] > dist[r][c][step] + cost) {
                    dist[nr][nc][(step + 1)%3] = dist[r][c][step] + cost;
                    pq.push({-dist[nr][nc][(step + 1)%3], State(nr, nc, (step + 1)%3)});
                }
            }
        }
    }

    printf("%d\n", min(dist[N][N][0], min(dist[N][N][1], dist[N][N][2])));
}
