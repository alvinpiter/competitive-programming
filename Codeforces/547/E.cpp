#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

LL H, prefixSum[MAXN + 3];
int n;

//Is it possible to end the game after numCycle cycles
LL check(LL numCycle) {
    LL tempH = H + prefixSum[n] * numCycle;

    if (tempH <= 0)
        return numCycle * n;

    for (int i = 1; i <= n; i++) {
        if (tempH + prefixSum[i] <= 0)
            return numCycle * n + i;
    }

    return -1;
}

int main() {
    cin >> H >> n;

    prefixSum[0] = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;

        prefixSum[i] = prefixSum[i - 1] + a;
    }

    for (int i = 1; i <= n; i++) {
        if (prefixSum[i] <= -H) {
            cout << i << endl;
            return 0;
        }
    }

    if (prefixSum[n] >= 0) {
        cout << -1 << endl;
        return 0;
    }

    LL lo = 1, hi = H/abs(prefixSum[n]) + 10, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        if (check(mid) != -1)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    cout << check(lo) << endl;
}
