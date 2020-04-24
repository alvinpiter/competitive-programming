#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, a, b, c, d;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> a >> b >> c >> d;

        if (n * (a + b) < c - d || n * (a - b) > c + d)
            cout << "No\n";
        else
            cout << "Yes\n";
    }
}
