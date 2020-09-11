#include<bits/stdc++.h>
using namespace std;

int main() {
    int q, n, k, lo, hi;

    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> n >> k;

        lo = 1;
        hi = 2e8;
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;

            lo = max(lo, max(1, a - k));
            hi = min(hi, a + k);
        }

        if (lo > hi)
            cout << -1 << endl;
        else
            cout << hi << endl;
    }
}
