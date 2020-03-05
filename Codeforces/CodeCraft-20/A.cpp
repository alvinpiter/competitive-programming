#include<bits/stdc++.h>
using namespace std;

int t, n, m, quota, a[1003];

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> m;

        quota = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];

            if (i > 1)
                quota += a[i];
        }

        cout << a[1] + min(m - a[1], quota) << endl;
    }
}
