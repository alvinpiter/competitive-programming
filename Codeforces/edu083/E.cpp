#include<bits/stdc++.h>
using namespace std;
#define MAXN 500

int n, a[MAXN + 3], shrinked[MAXN + 3][MAXN + 3], minLen[MAXN + 3][MAXN + 3];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    //Base case
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            shrinked[i][j] = -1;
            minLen[i][j] = j - i + 1;

            if (i == j)
                shrinked[i][j] = a[i];
        }
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l <= n; l++) {
            int r = l + len - 1;

            if (r > n)
                continue;

            for (int k = l; k < r; k++) {
                if (shrinked[l][k] != -1 && shrinked[k + 1][r] != -1 && shrinked[l][k] == shrinked[k + 1][r])
                    shrinked[l][r] = shrinked[l][k] + 1;

                if (shrinked[l][r] != -1)
                    minLen[l][r] = 1;
                else
                    minLen[l][r] = min(minLen[l][r], minLen[l][k] + minLen[k + 1][r]);
            }
        }
    }

    cout << minLen[1][n] << endl;
}
