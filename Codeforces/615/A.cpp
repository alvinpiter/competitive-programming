#include<bits/stdc++.h>
using namespace std;

int t, n, a, b, c, all, each;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> a >> b >> c >> n;

        all = (n + a + b + c);
        each = all/3;

        if (all%3 == 0 && each >= a && each >= b && each >= c)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
