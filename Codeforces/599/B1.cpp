#include<bits/stdc++.h>
using namespace std;

int main() {
    int tc, n, l, r;
    string s, t;

    cin >> tc;
    for (int cases = 1; cases <= tc; cases++) {
        cin >> n;
        cin >> s >> t;

        l = r = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] != t[i]) {
                l = i;
                break;
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] != t[i]) {
                r = i;
                break;
            }
        }

        if (l == -1)
            cout << "Yes\n";
        else {
            string first = s.substr(0, l) + t[r] + s.substr(l + 1);
            string second = t.substr(0, r) + s[l] + t.substr(r + 1);

            if (first == second) {
                cout << "Yes\n";
                continue;
            }

            first = s.substr(0, r) + t[l] + s.substr(r + 1);
            second = t.substr(0, l) + s[r] + t.substr(l + 1);

            if (first == second) {
                cout << "Yes\n";
                continue;
            }

            cout << "No\n";
        }
    }
}
