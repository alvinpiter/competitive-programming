#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e15
#define MAXN 5000

/*
Algorithm:
dp[i][j] -> maximum score reachable if we repost j pics out of the first i pics and we repost i-th pic.

Need range minimum query to make the complexity O(N^2 log N). We can also use deque to make the complexity O(N^2).
*/

int n, k, x, a[MAXN + 3];
LL dp[MAXN + 3][MAXN + 3];

int main() {
    scanf("%d%d%d", &n, &k, &x);

    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    //base case
    for (int i = 1; i <= n; i++)
        dp[i][1] = (i > k ? -INF : a[i]);

    for (int j = 1; j <= x; j++)
        dp[0][j] = -INF;

    deque<int> dq;
    for (int j = 2; j <= x; j++) {
        dq.clear();
        for (int i = 1; i <= n; i++) {
            //update dq
            while (!dq.empty() && dq.front() < i - k)
                dq.pop_front();

            while (!dq.empty() && dp[i - 1][j - 1] > dp[dq.back()][j - 1])
                dq.pop_back();

            dq.push_back(i - 1);

            dp[i][j] = (LL) a[i] + dp[dq.front()][j - 1];
        }
    }

    LL ans = -INF;
    for (int i = max(1, n - k + 1); i <= n; i++)
        ans = max(ans, dp[i][x]);

    if (ans < 0)
        printf("-1\n");
    else
        printf("%lld\n", ans);
}
