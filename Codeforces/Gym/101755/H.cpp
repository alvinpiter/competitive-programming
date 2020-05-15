#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, d, startR, startC, finishR, finishC;
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    cin >> n >> m >> d;

    char grid[n + 3][m + 3];
    queue<pair<int, int> > qMonsters, qPlayer;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'M') {
                qMonsters.push({i, j});
            }

            if (grid[i][j] == 'S') {
                startR = i;
                startC = j;
            }

            if (grid[i][j] == 'F') {
                finishR = i;
                finishC = j;
            }
        }
    }

    for (int dis = 1; dis <= d; dis++) {
        int sz = (int) qMonsters.size();
        for (int rep = 1; rep <= sz; rep++) {
            auto front = qMonsters.front(); qMonsters.pop();
            int ur = front.first, uc = front.second;

            for (int dir = 0; dir < 4; dir++) {
                int vr = ur + dr[dir];
                int vc = uc + dc[dir];
                if (vr >= 1 && vr <= n && vc >= 1 && vc <= m && grid[vr][vc] != 'M') {
                    grid[vr][vc] = 'M';
                    qMonsters.push({vr, vc});
                }
            }
        }
    }

    if (grid[startR][startC] == 'M') {
        cout << -1 << endl;
        return 0;
    }

    int dist[n + 3][m + 3];
    memset(dist, -1, sizeof(dist));

    dist[startR][startC] = 0;
    qPlayer.push({startR, startC});

    while (!qPlayer.empty()) {
        auto front = qPlayer.front(); qPlayer.pop();
        int ur = front.first, uc = front.second;

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir], vc = uc + dc[dir];
            if (vr >= 1 && vr <= n && vc >= 1 && vc <= m && grid[vr][vc] != 'M' && dist[vr][vc] == -1) {
                dist[vr][vc] = 1 + dist[ur][uc];
                qPlayer.push({vr, vc});
            }
        }
    }

    cout << dist[finishR][finishC] << endl;
}
