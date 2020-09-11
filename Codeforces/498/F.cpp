#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 20

int n, m, middle;
LL k, grid[MAXN + 3][MAXN + 3], answer;
map<LL, LL> cnt[MAXN + 3][MAXN + 3];

void searchTopLeft(int r, int c, LL currentXor, int step) {
    currentXor ^= grid[r][c];
    if (step == middle) {
        cnt[r][c][currentXor] += 1;
        return;
    }

    if (r < n - 1)
        searchTopLeft(r + 1, c, currentXor, step + 1);

    if (c < m - 1)
        searchTopLeft(r, c + 1, currentXor, step + 1);
}

void searchBottomRight(int r, int c, LL currentXor, int step) {
    if (step == n + m - 2 - middle) {
        answer += cnt[r][c][k ^ currentXor];
        return;
    }

    if (r > 0)
        searchBottomRight(r - 1, c, currentXor ^ grid[r][c], step + 1);

    if (c > 0)
        searchBottomRight(r, c - 1, currentXor ^ grid[r][c], step + 1);
}

int main() {
    cin >> n >> m >> k;

    middle = (n + m - 2)/2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    answer = 0;

    searchTopLeft(0, 0, 0, 0);
    searchBottomRight(n - 1, m - 1, 0, 0);

    cout << answer << endl;
}
