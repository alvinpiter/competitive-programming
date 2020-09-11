#include<bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    int l, r;

    cin >> s >> t;

    if (s.length() != t.length()) {
        cout << "NO\n";
        return 0;
    }

    l = s.length();
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != t[i]) {
            l = i;
            break;
        }
    }

    r = -1;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] != t[i]) {
            r = i;
            break;
        }
    }

    if (r == -1) {
        cout << "YES\n";
        return 0;
    }

    reverse(s.begin() + l, s.begin() + r + 1);

    if (s == t) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
