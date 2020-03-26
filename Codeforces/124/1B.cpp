#include<bits/stdc++.h>
using namespace std;
#define MAXN 1500

int N, M, startR, startC;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
char grid[MAXN + 3][MAXN + 3];
bool exist = false;
bool visited[MAXN + 3][MAXN + 3];
pair<int, int> where[MAXN + 3][MAXN + 3];

int mod(int n, int m) {
    if (n >= 0)
        return n%m;
    else {
        int temp = (abs(n)/m + (abs(n)%m == 0 ? 0 : 1)) * m;
        return temp + n;
    }
}

bool BFS(int r, int c) {
    queue<int> qR, qC;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visited[i][j] = false;
            where[i][j] = {-1, -1};
        }
    }

    qR.push(r); qC.push(c);
    visited[mod(r, N)][mod(c, M)] = true;
    where[mod(r, N)][mod(c, M)] = {r, c};

    while (!qR.empty()) {
        int ur = qR.front(); qR.pop();
        int uc = qC.front(); qC.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nr = ur + dr[dir];
            int nc = uc + dc[dir];

            if (grid[mod(nr, N)][mod(nc, M)] == '#')
                continue;

            if (visited[mod(nr, N)][mod(nc, M)]) {
                if (where[mod(nr, N)][mod(nc, M)] != make_pair(nr, nc))
                    return true;
            } else {
                visited[mod(nr, N)][mod(nc, M)] = true;
                where[mod(nr, N)][mod(nc, M)] = {nr, nc};
                qR.push(nr);
                qC.push(nc);
            }
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                startR = i;
                startC = j;
            }
        }
    }

    if (BFS(startR, startC))
        cout << "Yes\n";
    else
        cout << "No\n";
}
