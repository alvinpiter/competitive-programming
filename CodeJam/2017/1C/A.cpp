#include<bits/stdc++.h>
using namespace std;
#define INF 1e16
#define MAXN 1000

/*
Observe that the circular area is equal to the base pancake.
So if we fix the base of the pancake stack, we need to maximize the 2*pi*r*h of the remaining K - 1 pancakes. This can be done with dp.
*/

int T, N, K;
double dp[MAXN + 3][MAXN + 3];
vector<pair<int, int> > pancakes;

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &K);

        pancakes.clear();
        for (int i = 0; i < N; i++) {
            int r, h;
            scanf("%d%d", &r, &h);

            pancakes.push_back({r, h});
        }

        sort(pancakes.begin(), pancakes.end());

        //base case
        for (int i = 0; i < N; i++)
            dp[i][0] = 0;

        for (int j = 1; j <= K; j++)
            dp[0][j] = -INF;

        dp[0][1] = 2 * M_PI * pancakes[0].first * pancakes[0].second;

        for (int i = 1; i < N; i++) {
            for (int j = 1; j <= K; j++) {
                dp[i][j] = -INF;

                dp[i][j] = max(dp[i][j], dp[i - 1][j]); //leave
                dp[i][j] = max(dp[i][j], 2 * M_PI * pancakes[i].first * pancakes[i].second + dp[i - 1][j - 1]); //take
            }
        }

        double area = 0;
        for (int base = 0; base < N; base++) {
            int r = pancakes[base].first;
            int h = pancakes[base].second;
            double tempArea = M_PI * r * r + 2 * M_PI * r * h;

            if (K > 1) {
                if (base > 0)
                    tempArea += dp[base - 1][K - 1];
            }

            area = max(area, tempArea);
        }

        printf("Case #%d: %.8lf\n", cases, area);
    }
}
