#include<bits/stdc++.h>
using namespace std;

int t, n, a[103], b[103];

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];

        for (int i = 0; i < n; i++)
            cin >> b[i];

        sort(a, a + n);
        sort(b, b + n);

        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;

        for (int i = 0; i < n; i++)
            cout << b[i] << " ";
        cout << endl;
    }
}
