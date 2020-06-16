#include<bits/stdc++.h>
using namespace std;
#define MAXN 262144
#define MAXX 60

/*
dp[i][x] = index j such that i..j can be merged into x
*/

int N, num[MAXN + 3], dp[MAXN + 3][MAXX + 3], answer;

int main() {
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> num[i];

    answer = 0;
    for (int x = 1; x <= 60; x++) {
        for (int i = 1; i <= N; i++) {
            if (num[i] > x)
                dp[i][x] = -1;
            else if (num[i] == x)
                dp[i][x] = i;
            else {
                int j = dp[i][x - 1];
                if (j != -1 && j < N && dp[j + 1][x - 1] != -1) {
                    dp[i][x] = dp[j + 1][x - 1];
                } else {
                    dp[i][x] = -1;
                }
            }

            if (dp[i][x] != -1)
                answer = max(answer, x);
        }
    }

    cout << answer << endl;
}
