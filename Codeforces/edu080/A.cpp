#include<bits/stdc++.h>
using namespace std;

int main() {
    int T, n, d;

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> n >> d;
        if (n >= d)
            cout << "YES\n";
        else {
            int mini = 1e9;
            for (int x = 0; x * x <= d; x++) {
                mini = min(mini, x + d/(x + 1) + (d%(x + 1) == 0 ? 0 : 1));
            }

            if (mini <= n)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
}
