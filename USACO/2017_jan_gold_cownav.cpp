#include<bits/stdc++.h>
using namespace std;
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define MAXN 20
#define INF 1000000000

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

struct CowState {
    int row, col, direction;
    CowState(int _row, int _col, int _direction): row(_row), col(_col), direction(_direction) {}

    void turnLeft() {
        direction = (direction + 3)%4;
    }

    void turnRight() {
        direction = (direction + 1)%4;
    }

    void moveForward() {
        row += dr[direction];
        col += dc[direction];
    }
};

int N, dist[MAXN + 3][MAXN + 3][4][MAXN + 3][MAXN + 3][4];
char grid[MAXN + 3][MAXN + 3];

bool hasReachedGoal(CowState p) {
    return (p.row == 1 && p.col == N);
}

pair<CowState, CowState> turnLeft(pair<CowState, CowState> p) {
    if (!hasReachedGoal(p.first))
        p.first.turnLeft();

    if (!hasReachedGoal(p.second))
        p.second.turnLeft();

    return p;
}

pair<CowState, CowState> turnRight(pair<CowState, CowState> p) {
    if (!hasReachedGoal(p.first))
        p.first.turnRight();

    if (!hasReachedGoal(p.second))
        p.second.turnRight();

    return p;
}

pair<CowState, CowState> moveForward(pair<CowState, CowState> p) {
    int r1 = p.first.row + dr[p.first.direction], c1 = p.first.col + dc[p.first.direction];
    if (r1 >= 1 && r1 <= N && c1 >= 1 && c1 <= N && grid[r1][c1] == 'E' && !hasReachedGoal(p.first))
        p.first.moveForward();

    int r2 = p.second.row + dr[p.second.direction], c2 = p.second.col + dc[p.second.direction];
    if (r2 >= 1 && r2 <= N && c2 >= 1 && c2 <= N && grid[r2][c2] == 'E' && !hasReachedGoal(p.second))
        p.second.moveForward();

    return p;
}

int getDist(pair<CowState, CowState> p) {
    return dist[p.first.row][p.first.col][p.first.direction][p.second.row][p.second.col][p.second.direction];
}

void setDist(pair<CowState, CowState> p, int value) {
    dist[p.first.row][p.first.col][p.first.direction][p.second.row][p.second.col][p.second.direction] = value;
}

int main() {
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int d1 = 0; d1 < 4; d1++) {
                for (int k = 1; k <= N; k++) {
                    for (int l = 1; l <= N; l++) {
                        for (int d2 = 0; d2 < 4; d2++)
                            dist[i][j][d1][k][l][d2] = INF;
                    }
                }
            }
        }
    }

    queue<pair<CowState, CowState> > Q;
    Q.push({CowState(N, 1, UP), CowState(N, 1, RIGHT)});
    dist[N][1][UP][N][1][RIGHT] = 0;

    while (!Q.empty()) {
        auto front = Q.front(); Q.pop();

        auto l = turnLeft(front);
        if (getDist(l) == INF) {
            setDist(l, getDist(front) + 1);
            Q.push(l);
        }

        auto r = turnRight(front);
        if (getDist(r) == INF) {
            setDist(r, getDist(front) + 1);
            Q.push(r);
        }

        auto f = moveForward(front);
        if (getDist(f) == INF) {
            setDist(f, getDist(front) + 1);
            Q.push(f);
        }
    }

    int answer = INF;
    for (int d1 = 0; d1 < 4; d1++) {
        for (int d2 = 0; d2 < 4; d2++) {
            answer = min(answer, dist[1][N][d1][1][N][d2]);
        }
    }

    cout << answer << endl;
}
