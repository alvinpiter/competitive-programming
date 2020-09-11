#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, k, a[33], b[33], sumA;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> k;

        sumA = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sumA += a[i];
        }

        for (int i = 0; i < n; i++)
            cin >> b[i];

        sort(a, a + n);
        sort(b, b + n, greater<int>());

        for (int i = 0; i < min(n, k); i++) {
            if (a[i] < b[i]) {
                sumA -= a[i];
                sumA += b[i];
            }
        }

        cout << sumA << endl;
    }
}
