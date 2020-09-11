#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, pos8;
    string s;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> s;

        pos8 = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] == '8') {
                pos8 = i;
                break;
            }
        }

        if (pos8 != -1 && n - pos8 >= 11)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
