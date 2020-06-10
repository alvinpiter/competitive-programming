#include<bits/stdc++.h>
using namespace std;
#define MAXN 200

int R, C, rowSum[MAXN + 3][MAXN + 3], colSum[MAXN + 3][MAXN + 3], answer;
char grid[MAXN + 3][MAXN + 3];

bool isEmptyRow(int r, int c1, int c2) {
    return (rowSum[r][c2] - rowSum[r][c1 - 1] == 0);
}

bool isEmptyColumn(int c, int r1, int r2) {
    return (colSum[c][r2] - colSum[c][r1 - 1] == 0);
}

int main() {
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);

    cin >> R >> C;

    memset(rowSum, 0, sizeof(rowSum));
    memset(colSum, 0, sizeof(colSum));
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'X') {
                rowSum[i][j] = 1;
                colSum[j][i] = 1;
            }
        }
    }

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++)
            rowSum[i][j] += rowSum[i][j - 1];
    }

    for (int j = 1; j <= C; j++) {
        for (int i = 1; i <= R; i++)
            colSum[j][i] += colSum[j][i - 1];
    }

    answer = 0;
    for (int c1 = 1; c1 <= C; c1++) {
        for (int c2 = c1; c2 <= C; c2++) {
            int lastEmptyRow = -1;

            for (int i = 1; i <= R; i++) {
                if (isEmptyRow(i, c1, c2)) {
                    if (lastEmptyRow != -1) {
                        if (isEmptyColumn(c1, lastEmptyRow, i) && isEmptyColumn(c2, lastEmptyRow, i)) {
                            answer = max(answer, (c2 - c1 + 1)*(i - lastEmptyRow + 1));
                        } else {
                            lastEmptyRow = i;
                        }
                    } else {
                        lastEmptyRow = i;
                    }
                }
            }
        }
    }

    cout << answer << endl;
}
