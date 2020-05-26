#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, s[53];

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> s[i];

        int miniDiff = 1e9;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++)
                miniDiff = min(miniDiff, abs(s[i] - s[j]));
        }

        cout << miniDiff << endl;
    }
}
