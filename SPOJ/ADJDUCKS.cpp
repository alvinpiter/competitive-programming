#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int N;
LL a[MAXN + 3], dp[MAXN + 3];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> a[i];

    sort(a, a + N);

    dp[0] = (LL) 5 * (1e18);
    dp[1] = a[1] - a[0];
    dp[2] = (a[2] - a[0]);
    for (int i = 3; i < N; i++) {
        dp[i] = dp[i - 2] + (a[i] - a[i - 1]);
        dp[i] = min(dp[i], dp[i - 3] + (a[i] - a[i - 2]));
    }

    cout << dp[N - 1] << endl;
}
