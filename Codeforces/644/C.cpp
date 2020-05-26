#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, a[53], cntOdd, cntEven;
    bool consecutiveExist;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        sort(a + 1, a + n + 1);

        cntOdd = cntEven = 0;
        consecutiveExist = false;

        for (int i = 1; i <= n; i++) {
            if (a[i]%2 == 0)
                cntEven += 1;
            else
                cntOdd += 1;

            if (i > 1 && a[i] - a[i - 1] == 1)
                consecutiveExist = true;
        }

        if (cntOdd%2 == 0 && cntEven%2 == 0)
            cout << "YES\n";
        else if (cntOdd%2 == 1 && cntEven%2 == 1) {
            if (consecutiveExist)
                cout << "YES\n";
            else
                cout << "NO\n";
        } else
            cout << "NO\n";
    }
}
