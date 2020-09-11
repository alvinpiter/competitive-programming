#include<bits/stdc++.h>
using namespace std;
#define MAXR 3000

int R, C, H, W, grid[MAXR + 3][MAXR + 3], prefix[MAXR + 3][MAXR + 3];

void add(int r, int c, int val) {
    prefix[r][c] += val;
    prefix[r][c] += prefix[r - 1][c];
    prefix[r][c] += prefix[r][c - 1];
    prefix[r][c] -= prefix[r - 1][c - 1];
}

int query(int r1, int c1, int r2, int c2) {
    int result = prefix[r2][c2];
    result -= prefix[r1 - 1][c2];
    result -= prefix[r2][c1 - 1];
    result += prefix[r1 - 1][c1 - 1];

    return result;
}

int main() {
    cin >> R >> C >> H >> W;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++)
            cin >> grid[i][j];
    }

    int lo = 1, hi = R * C, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        bool canBeLower = false;

        memset(prefix, 0, sizeof(prefix));
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                int val;
                if (grid[i][j] == mid)
                    val = 0;
                else if (grid[i][j] < mid)
                    val = -1;
                else
                    val = 1;

                add(i, j, val);

                if (i >= H && j >= W) {
                    int q = query(i - H + 1, j - W + 1, i, j);
                    if (q <= 0)
                        canBeLower = true;
                }
            }
        }

        if (canBeLower)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    cout << lo << endl;
}
