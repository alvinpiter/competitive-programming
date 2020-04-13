#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int q, n, m, a, b;
char grid[MAXN + 3][MAXN + 3], temp[MAXN + 3];
vector<pair<int, int> > pos;

int main() {
    scanf("%d", &q);
    for (int cases = 1; cases <= q; cases++) {
        scanf("%d%d%d%d", &n, &m, &a, &b);

        for (int i = 0; i < n; i++) {
            scanf("%s", grid[i]);
        }

        pos.clear();
        for (int i = 0; i < a; i++) {
            scanf("%s", temp);
            for (int j = 0; j < b; j++) {
                if (temp[j] == 'x')
                    pos.push_back({i, j});
            }
        }

        bool valid = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'x') {
                    int dr = i - pos[0].first;
                    int dc = j - pos[0].second;

                    for (int k = 0; k < (int) pos.size(); k++) {
                        int r = pos[k].first + dr;
                        int c = pos[k].second + dc;

                        if (r < 0 || r >= n || c < 0 || c >= m || grid[r][c] != 'x') {
                            valid = false;
                            break;
                        } else {
                            grid[r][c] = '.';
                        }
                    }
                }

                if (!valid) break;
            }

            if (!valid) break;
        }

        if (valid) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
        }
    }
}
