#include<bits/stdc++.h>
using namespace std;

int t, n, a[103];

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];

        sort(a, a + n);
        for (int i = n - 1; i >= 0; i--)
            cout << a[i] << " ";
        cout << endl;
    }
}
