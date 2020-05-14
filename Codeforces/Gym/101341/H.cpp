#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int n, m, a[MAXN + 3][MAXN + 3];
int topLeft[MAXN + 3][MAXN + 3], topRight[MAXN + 3][MAXN + 3];
int bottomLeft[MAXN + 3][MAXN + 3], bottomRight[MAXN + 3][MAXN + 3];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    memset(topLeft, 0, sizeof(topLeft));
    memset(topRight, 0, sizeof(topRight));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            topLeft[i][j] = max(a[i][j], max(topLeft[i - 1][j], topLeft[i][j - 1]));
        }

        for (int j = m; j >= 1; j--) {
            topRight[i][j] = max(a[i][j], max(topRight[i - 1][j], topRight[i][j + 1]));
        }
    }

    memset(bottomLeft, 0, sizeof(bottomLeft));
    memset(bottomRight, 0, sizeof(bottomRight));
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            bottomLeft[i][j] = max(a[i][j], max(bottomLeft[i + 1][j], bottomLeft[i][j - 1]));
        }

        for (int j = m; j >= 1; j--) {
            bottomRight[i][j] = max(a[i][j], max(bottomRight[i + 1][j], bottomRight[i][j + 1]));
        }
    }

    int mini = 2e9;
    int ans1, ans2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int temp = 0;
            temp = max(temp, topLeft[i - 1][j - 1]);
            temp = max(temp, topRight[i - 1][j + 1]);
            temp = max(temp, bottomLeft[i + 1][j - 1]);
            temp = max(temp, bottomRight[i + 1][j + 1]);

            if (temp < mini) {
                mini = temp;
                ans1 = i;
                ans2 = j;
            }
        }
    }

    cout << ans1 << " " << ans2 << endl;
}
