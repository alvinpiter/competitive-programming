#include<bits/stdc++.h>
using namespace std;
#define MAXN 2005

bool isInsideGrid(int x, int y) {
    return (x >= 1 && x <= MAXN && y >= 1 && y <= MAXN);
}

int id(int x, int y) {
    return (y - 1)*MAXN + x;
}

int N, numCC;
bool visited[MAXN + 3][MAXN + 3];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
set<int> blocked[MAXN * MAXN + 3];

void BFS(int x, int y) {
    queue<int> qx, qy;
    visited[x][y] = true;
    qx.push(x);
    qy.push(y);

    while (!qx.empty()) {
        int x = qx.front(); qx.pop();
        int y = qy.front(); qy.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            bool isBlocked = (blocked[id(x, y)].find(id(nx, ny)) != blocked[id(x, y)].end());

            if (isInsideGrid(nx, ny) && !isBlocked && !visited[nx][ny]) {
                visited[nx][ny] = true;
                qx.push(nx);
                qy.push(ny);
            }
        }
    }
}

int main() {
    freopen("gates.in", "r", stdin);
    freopen("gates.out", "w", stdout);

    cin >> N;

    int currX = 1002, currY = 1002;
    for (int i = 1; i <= N; i++) {
        char dir;
        cin >> dir;

        int f, s;

        if (dir == 'N') {
            currY += 1;
            f = id(currX, currY);
            s = id(currX + 1, currY);
        }

        if (dir == 'E') {
            currX += 1;
            f = id(currX, currY);
            s = id(currX, currY + 1);
        }

        if (dir == 'S') {
            f = id(currX, currY);
            s = id(currX + 1, currY);
            currY -= 1;
        }

        if (dir == 'W') {
            f = id(currX, currY);
            s = id(currX, currY + 1);
            currX -= 1;
        }

        blocked[f].insert(s);
        blocked[s].insert(f);
    }

    memset(visited, false, sizeof(visited));

    numCC = 0;
    for (int i = 1; i <= MAXN; i++) {
        for (int j = 1; j <= MAXN; j++) {
            if (!visited[i][j]) {
                numCC += 1;
                BFS(i, j);
            }
        }
    }

    cout << numCC - 1 << endl;
}
