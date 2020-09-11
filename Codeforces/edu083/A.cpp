#include<bits/stdc++.h>
using namespace std;

int t, n, m;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> m;
        if (n%m == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
