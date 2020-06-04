#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

/*
dp[i][mod] -> is it possible for the characters from i to len-1 to congruent to mod modulo d
*/

string s;
int d, len, p10[MAXN + 3];
bool dp[MAXN + 3][MAXN + 3];

int main() {
    cin >> s >> d;

    len = (int) s.length();

    p10[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        p10[i] = (10 * p10[i - 1])%d;

    memset(dp, false, sizeof(dp));

    dp[len][0] = true;
    for (int i = len - 1; i >= 0; i--) {
        for (int m = 0; m < d; m++) {
            for (int digit = (i == 0 ? 1 : 0); digit < 10; digit++) {
                if (s[i] != '?' && (s[i] - '0') != digit)
                    continue;

                int need = (m - (digit*p10[len - 1 - i])%d + d)%d;
                dp[i][m] |= dp[i + 1][need];
            }
        }
    }

    if (dp[0][0] == false)
        printf("*\n");
    else {
        int currentMod = 0;
        for (int i = 0; i < len; i++) {
            if (s[i] != '?') {
                printf("%c", s[i]);

                int digit = s[i] - '0';
                currentMod = (currentMod + digit * p10[len - 1 - i])%d;
            } else {
                for (int digit = (i == 0 ? 1 : 0); digit < 10; digit++) {
                    int newMod = (currentMod + digit * p10[len - 1 - i])%d;
                    int need = (d - newMod + d)%d;

                    if (dp[i + 1][need]) {
                        printf("%d", digit);
                        currentMod = newMod;
                        break;
                    }
                }
            }
        }

        printf("\n");
    }
}
