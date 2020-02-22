#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 1000000
#define OFFSET 2

//dp[idx][lastPos][mini][maxi] = number of ways to fill idx to N when the last height was last pos and min height is mini and max height is maxi
//Need to use dp on the fly technique

int N, M;
char C[MAXN + 3];
int prefixPos[MAXN + 3], prefixMini[MAXN + 3], prefixMaxi[MAXN + 3];
int dp[2][5][5][5], t;
string S;

int main() {
    cin >> N >> M;

    prefixPos[0] = prefixMini[0] = prefixMaxi[0] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> C[i];

        prefixPos[i] = prefixPos[i - 1] + (C[i] == 'L' ? -1 : +1);
        prefixMini[i] = min(prefixMini[i - 1], prefixPos[i]);
        prefixMaxi[i] = max(prefixMaxi[i - 1], prefixPos[i]);
    }

    t = 0;

    //base case
    for (int last = -2; last <= 2; last++) {
        for (int mini = -2; mini <= 2; mini++) {
            for (int maxi = -2; maxi <= 2; maxi++) {
                if (mini <= maxi && maxi - mini <= 2 && last >= mini && last <= maxi)
                    dp[t][last + OFFSET][mini + OFFSET][maxi + OFFSET] = 1;
                else
                    dp[t][last + OFFSET][mini + OFFSET][maxi + OFFSET] = 0;
            }
        }
    }

    int answer = 0;
    for (int i = N; i >= 1; i--) {
        t = 1 - t;

        //calculate dp
        for (int last = -2; last <= 2; last++) {
            for (int mini = -2; mini <= 2; mini++) {
                for (int maxi = -2; maxi <= 2; maxi++) {
                    dp[t][last + OFFSET][mini + OFFSET][maxi + OFFSET] = 0;

                    if (mini <= maxi && maxi - mini <= 2 && last >= mini && last <= maxi) {
                        if (max(last + 1, maxi) - mini <= 2)
                            dp[t][last + OFFSET][mini + OFFSET][maxi + OFFSET] += dp[1 - t][last + 1 + OFFSET][mini + OFFSET][max(last + 1, maxi) + OFFSET];

                        if (maxi - min(last - 1, mini) <= 2)
                            dp[t][last + OFFSET][mini + OFFSET][maxi + OFFSET] += dp[1 - t][last - 1 + OFFSET][min(last - 1, mini) + OFFSET][maxi + OFFSET];
                    }

                    dp[t][last + OFFSET][mini + OFFSET][maxi + OFFSET] %= M;
                }
            }
        }

        if (C[i] == 'P') {
            if (prefixPos[i - 1] - 1 >= -2)
                answer = (answer + dp[1 - t][(prefixPos[i - 1] - 1) + OFFSET][min(prefixPos[i - 1] - 1, prefixMini[i - 1]) + OFFSET][prefixMaxi[i - 1] + OFFSET])%M;
        }
    }

    answer = (answer + 1)%M;

    cout << answer << endl;
}
