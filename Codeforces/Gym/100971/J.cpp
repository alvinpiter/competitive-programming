#include<bits/stdc++.h>
using namespace std;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    int n, m;

    cin >> n >> m;

    char grid[n + 3][m + 3];
    bool visited[n + 3][m + 3];
    pair<int, int> prev[n + 3][m + 3], origin, destination;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == '1')
                origin = {i, j};

            if (grid[i][j] == '2')
                destination = {i, j};
        }
    }

    //Cell is good if it's degree is > 2
    bool goodCellExist = false;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '#')
                continue;

            int cnt = 0;
            for (int dir = 0; dir < 4; dir++) {
                int r = i + dr[dir], c = j + dc[dir];
                if (r >= 1 && r <= n && c >= 1 && c <= m && grid[r][c] != '#')
                    cnt += 1;
            }

            if (cnt > 2)
                goodCellExist = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            visited[i][j] = false;
            prev[i][j] = make_pair(i, j);
        }
    }

    queue<pair<int, int> > Q;
    Q.push(origin);
    visited[origin.first][origin.second] = true;

    bool cycleExist = false;
    while (!Q.empty()) {
        auto front = Q.front(); Q.pop();
        int ur = front.first, uc = front.second;

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir];
            int vc = uc + dc[dir];

            if (vr < 1 || vr > n || vc < 1 || vc > m || grid[vr][vc] == '#')
                continue;

            if (!visited[vr][vc]) {
                visited[vr][vc] = true;
                prev[vr][vc] = {ur, uc};
                Q.push({vr, vc});
            } else {
                if (vr != prev[ur][uc].first || vc != prev[ur][uc].second)
                    cycleExist = true;
            }
        }
    }

    if (goodCellExist || cycleExist)
        cout << "YES\n";
    else
        cout << "NO\n";
}

/*
3 6
1....2
#.##.#
#....#

2 5
1...2
##.##

2 3
#.#
.12

3 4
1..2
.##.
....
*/
