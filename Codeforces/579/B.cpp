#include<bits/stdc++.h>
using namespace std;
#define MAXN 100

int q, n, a[4 * MAXN + 3];

int main() {
    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> n;
        for (int i = 0; i < 4 * n; i++)
            cin >> a[i];

        sort(a, a + 4 * n);

        int l = 0, r = 4 * n - 1, targetArea = a[0] * a[4 * n - 1];
        bool valid = true;
        while (l < r) {
            if (a[l] * a[r] != targetArea || a[l + 1] != a[l] || a[r - 1] != a[r]) {
                valid = false;
                break;
            }

            l += 2;
            r -= 2;
        }

        if (valid)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
