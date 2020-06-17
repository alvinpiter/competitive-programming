#include<bits/stdc++.h>
using namespace std;
#define INF 1000000
#define MAXN 500
#define UP 0
#define DOWN 1

/*
0-1 BFS on state graph
*/

struct State {
    int r, c, gd; //gd is gravity direction, 0 if gravity is up, 1 otherwise
    State(int _r, int _c, int _gd): r(_r), c(_c), gd(_gd) {}
};

int N, M, dist[MAXN + 3][MAXN + 3][2];
pair<int, int> startPos, endPos;
char grid[MAXN + 3][MAXN + 3];

int main() {
    freopen("gravity.in", "r", stdin);
    freopen("gravity.out", "w", stdout);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'C')
                startPos = {i, j};
            if (grid[i][j] == 'D')
                endPos = {i, j};
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            dist[i][j][UP] = dist[i][j][DOWN] = INF;
        }
    }

    dist[startPos.first][startPos.second][DOWN] = 0;
    deque<State> dq;
    dq.push_back(State(startPos.first, startPos.second, DOWN));

    while (!dq.empty()) {
        auto front = dq.front(); dq.pop_front();
        int r = front.r, c = front.c, gd = front.gd, dr = (gd == UP ? -1 : 1);
        int nr = r + dr;

        //if out of the grid
        if (nr < 1 || nr > N)
            continue;

        //if next row is empty, fall
        if (grid[nr][c] != '#') {
            if (dist[nr][c][gd] == INF) {
                dist[nr][c][gd] = dist[r][c][gd];
                dq.push_front(State(nr, c, gd));
            }
        }

        //if next row is not empty
        if (grid[nr][c] == '#') {
            //try move left
            if (c > 1 && grid[r][c - 1] != '#' && dist[r][c - 1][gd] == INF) {
                dist[r][c - 1][gd] = dist[r][c][gd];
                dq.push_front(State(r, c - 1, gd));
            }

            //try move right
            if (c < M && grid[r][c + 1] != '#' && dist[r][c + 1][gd] == INF) {
                dist[r][c + 1][gd] = dist[r][c][gd];
                dq.push_front(State(r, c + 1, gd));
            }

            //try flip gravity
            if (dist[r][c][1 - gd] == INF) {
                dist[r][c][1 - gd] = 1 + dist[r][c][gd];
                dq.push_back(State(r, c, 1 - gd));
            }
        }
    }

    int ans = min(dist[endPos.first][endPos.second][UP], dist[endPos.first][endPos.second][DOWN]);
    if (ans < INF)
        cout << ans << endl;
    else
        cout << -1 << endl;
}
