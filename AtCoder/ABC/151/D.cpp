#include<bits/stdc++.h>
using namespace std;
#define MAXR 20

int R, C;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
char grid[MAXR + 3][MAXR + 3];

int getMaxDistance(int r, int c) {
    int dist[MAXR + 3][MAXR + 3];
    memset(dist, -1, sizeof(dist));

    queue<pair<int, int> > Q;
    Q.push({r, c});

    dist[r][c] = 0;

    int maxi = 0;
    while (!Q.empty()) {
        auto front = Q.front(); Q.pop();
        int ur = front.first, uc = front.second;

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir];
            int vc = uc + dc[dir];

            if (vr >= 1 && vr <= R && vc >= 1 && vc <= C && grid[vr][vc] == '.' && dist[vr][vc] == -1) {
                dist[vr][vc] = dist[ur][uc] + 1;
                Q.push({vr, vc});

                maxi = max(maxi, dist[vr][vc]);
            }
        }
    }

    return maxi;
}

int main() {
    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> grid[i][j];
        }
    }

    int maxi = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (grid[i][j] == '.') {
                maxi = max(maxi, getMaxDistance(i, j));
            }
        }
    }

    cout << maxi << endl;
}
