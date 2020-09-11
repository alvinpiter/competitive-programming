#include<bits/stdc++.h>
using namespace std;
#define INF 2000000007
#define MAXN 100000
#define DEBUG true

/*
lef[j] = smallest index i such that the difference between maximum elements in i..j is <= s
dp[i] = minimal number of partition to for the the first i numbers

dp[i] = min(dp[j - 1] + 1), where lef[i] <= j <= i - l + 1
*/

int n, s, l, a[MAXN + 3], lef[MAXN + 3], dp[MAXN + 3];

void precompute() {
    /*
    mini stores indices of element whose values are increasing
    maxi stores indices of element whose values are decreasing
    */
    deque<int> mini, maxi;

    int ptr = 1;
    for (int i = 1; i <= n; i++) {
        while (!mini.empty() && a[mini.back()] > a[i])
            mini.pop_back();

        while (!maxi.empty() && a[maxi.back()] < a[i])
            maxi.pop_back();

        mini.push_back(i);
        maxi.push_back(i);

        while (a[maxi.front()] - a[mini.front()] > s) {
            if (mini.front() == ptr) mini.pop_front();
            if (maxi.front() == ptr) maxi.pop_front();

            ptr += 1;
        }

        lef[i] = ptr;
    }
}

int main() {
    cin >> n >> s >> l;

    if (l > n) {
        printf("-1\n");
        return 0;
    }

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    precompute();

    dp[0] = 0;

    deque<int> dq;
    for (int i = 1; i <= n; i++) {
        int idx = max(0, i - l);
        while (!dq.empty() && dp[dq.back()] >= dp[idx])
            dq.pop_back();

        dq.push_back(idx);

        while (!dq.empty() && dq.front() < lef[i] - 1)
            dq.pop_front();

        if (dq.empty())
            dp[i] = INF;
        else
            dp[i] = 1 + dp[dq.front()];
    }

    if (dp[n] < INF)
        printf("%d\n", dp[n]);
    else
        printf("-1\n");
}
