#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 800

/*
Edge case: Bee already reaach M before Mecho starts to move
*/

int N, S;
char grid[MAXN + 3][MAXN + 3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

bool isInsideGrid(int r, int c) {
    return r >= 1 && r <= N && c >= 1 && c <= N;
}

/*
check if Mecho can get away after waiting startingTime
Here the unit of time is 1/S minute. That means Mecho will move 1 cell per unit time, and
bee will move 1 cell per S unit time.
*/
bool check(int startingTime) {
    int distBee[MAXN + 3][MAXN + 3], distMecho[MAXN + 3][MAXN + 3];

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            distBee[i][j] = distMecho[i][j] = INF;
        }
    }

    queue<pair<int, int> > qBee;
    queue<pair<int, int> > qMecho;
    pair<int, int> startMecho;
    pair<int, int> goalMecho;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (grid[i][j] == 'H') {
                distBee[i][j] = 0;
                qBee.push({i, j});
            }

            if (grid[i][j] == 'M') {
                distMecho[i][j] = startingTime;
                qMecho.push({i, j});

                startMecho = {i, j};
            }

            if (grid[i][j] == 'D') {
                goalMecho = {i, j};
            }
        }
    }

    //BFS bee
    while (!qBee.empty()) {
        auto front = qBee.front(); qBee.pop();
        int ur = front.first, uc = front.second;

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir], vc = uc + dc[dir];

            if (isInsideGrid(vr, vc) && grid[vr][vc] != 'T' && grid[vr][vc] != 'D' && distBee[vr][vc] == INF) {
                distBee[vr][vc] = distBee[ur][uc] + S;
                qBee.push({vr, vc});
            }
        }
    }

    if (distBee[startMecho.first][startMecho.second] <= startingTime)
        return false;

    //BFS Mecho
    while (!qMecho.empty()) {
        auto front = qMecho.front(); qMecho.pop();
        int ur = front.first, uc = front.second;

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir], vc = uc + dc[dir];

            if (isInsideGrid(vr, vc) && grid[vr][vc] != 'T' && distMecho[ur][uc] + 1 < distBee[vr][vc] && distMecho[vr][vc] == INF) {
                distMecho[vr][vc] = distMecho[ur][uc] + 1;
                qMecho.push({vr, vc});
            }
        }
    }

    if (distMecho[goalMecho.first][goalMecho.second] == INF)
        return false;
    else
        return true;
}

int main() {
    scanf("%d%d", &N, &S);

    char temp[MAXN + 3];
    for (int i = 1; i <= N; i++) {
        scanf("%s", temp);
        for (int j = 1; j <= N; j++) {
            grid[i][j] = temp[j - 1];
        }
    }

    int lo = 0, hi = INF, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (check(mid))
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    if (hi == -1)
        printf("-1\n");
    else
        printf("%d\n", hi/S);
}

/*
7 3
TTTTTTT
TGGGGGT
TGGGGGT
MGGGGGD
TGGGGGT
TGGGGGT
THHHHHT

7 3
TTTTTTT
TGGGGGT
TGGGGGT
MGGGGGD
TGGGGGT
TGGGGGT
TGHHGGT
*/
