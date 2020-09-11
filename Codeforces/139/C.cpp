#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 1000

//dp[i][c] -> minimal pixel change needed to color first i color such that column i is colored c
int n, m, x, y;
int numBlackAtColumn[MAXN + 3], dp[MAXN + 3][2];

int main() {
    cin >> n >> m >> x >> y;

    memset(numBlackAtColumn, 0, sizeof(numBlackAtColumn));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;

            if (c == '#')
                numBlackAtColumn[j] += 1;
        }
    }

    dp[0][0] = dp[0][1] = 0;
    for (int i = 1; i <= m; i++) {
        if (i >= x) {
            int costBlack = 0;
            int costWhite = 0;

            dp[i][0] = dp[i][1] = INF;
            for (int j = i; j >= max(1, i - y + 1); j--) {
                costBlack += (n - numBlackAtColumn[j]);
                costWhite += numBlackAtColumn[j];

                if (i - j + 1 >= x) {
                    dp[i][0] = min(dp[i][0], costWhite + dp[j - 1][1]);
                    dp[i][1] = min(dp[i][1], costBlack + dp[j - 1][0]);
                }
            }
        } else {
            dp[i][0] = dp[i][1] = INF;
        }
    }

    cout << min(dp[m][0], dp[m][1]) << endl;
}
