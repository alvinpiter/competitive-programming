#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 30

int N, A, B;
char grid[MAXN + 3][MAXN + 3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int getMaxDistance(int r, int c) {
    int dist[MAXN + 3][MAXN + 3];
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            dist[i][j] = INF;
    }

    priority_queue<pair<int, pair<int, int> > > pq;
    dist[r][c] = 0;
    pq.push({-dist[r][c], {r, c}});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int ur = top.second.first, uc = top.second.second;

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir], vc = uc + dc[dir];

            if (vr >= 1 && vr <= N && vc >= 1 && vc <= N) {
                int cost = (grid[ur][uc] == grid[vr][vc] ? A : B);
                if (dist[vr][vc] > dist[ur][uc] + cost) {
                    dist[vr][vc] = dist[ur][uc] + cost;
                    pq.push({-dist[vr][vc], {vr, vc}});
                }
            }
        }
    }

    int maxi = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            maxi = max(maxi, dist[i][j]);
    }

    return maxi;
}

int main() {
    freopen("distant.in", "r", stdin);
    freopen("distant.out", "w", stdout);

    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            cin >> grid[i][j];
    }

    int answer = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            answer = max(answer, getMaxDistance(i, j));
        }
    }

    cout << answer << endl;
}
