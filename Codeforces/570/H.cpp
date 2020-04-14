#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100
#define MAXK 1e12

/*
dp[i][len] -> number of subsequence of length len ending at i
prv[c][i] -> largest j (j < i) such that s[j] = c
*/

int n;
LL k, dp[MAXN + 3][MAXN + 3];
int prv[26][MAXN + 3];
string s;

int main() {
    cin >> n >> k >> s;

    for (int c = 0; c < 26; c++) {
        for (int i = 1; i <= n + 1; i++) {
            prv[c][i] = -1;
            for (int j = i - 1; j >= 1; j--) {
                if (s[j - 1] - 'a' == c) {
                    prv[c][i] = j;
                    break;
                }
            }
        }
    }

    //base case
    for (int i = 1; i <= n; i++)
        dp[i][1] = 1;

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            dp[i][len] = 0;
            for (int c = 0; c < 26; c++) {
                if (prv[c][i] != -1) {
                    dp[i][len] += dp[prv[c][i]][len - 1];
                    dp[i][len] = min(dp[i][len], (LL) MAXK);
                }
            }
        }
    }

    LL answer = 0;
    for (int len = n; len >= 1; len--) {
        LL cnt = 0; //number of subsequence with length len
        for (int c = 0; c < 26; c++) {
            if (prv[c][n + 1] == -1) continue;

            cnt += dp[prv[c][n + 1]][len];
            cnt = min(cnt, (LL) MAXK);
        }

        LL take = min(cnt, k);
        answer += take * (n - len);
        k -= take;
    }

    //Add empty subsequence if needed
    if (k == 1) {
        k = 0;
        answer += n;
    }

    if (k > 0)
        cout << -1 << endl;
    else
        cout << answer << endl;
}
