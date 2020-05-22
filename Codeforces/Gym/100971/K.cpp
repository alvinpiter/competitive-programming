#include<bits/stdc++.h>
using namespace std;

bool isPalindrome(string s) {
    int l = 0, r = s.length() - 1;
    while (r >= l) {
        if (s[l] != s[r])
            return false;

        l += 1;
        r -= 1;
    }

    return true;
}

int main() {
    string s;
    int n;

    cin >> s;
    n = (int) s.length();

    if (isPalindrome(s)) {
        cout << "YES\n";
        cout << (n + 1)/2 << endl;
    } else {
        int l = 0, r = n - 1;
        while (s[l] == s[r]) {
            l += 1;
            r -= 1;
        }

        if (isPalindrome(s.substr(l + 1, r - (l + 1) + 1))) {
            cout << "YES\n";
            cout << l + 1 << endl;
        } else if (isPalindrome(s.substr(l, (r - 1) - l + 1))) {
            cout << "YES\n";
            cout << r + 1 << endl;
        } else
            cout << "NO\n";
    }
}
