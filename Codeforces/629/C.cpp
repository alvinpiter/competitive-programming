#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n;
    string s, a, b;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        cin >> s;

        a = "";
        b = "";

        int idx1;
        for (idx1 = 0; idx1 < n; idx1++) {
            if (s[idx1] == '2') {
                a += '1';
                b += '1';
            } else if (s[idx1] == '1') {
                a += '1';
                b += '0';

                break;
            } else {
                a += '0';
                b += '0';
            }
        }

        for (int i = idx1 + 1; i < n; i++) {
            if  (s[i] == '2') {
                a += '0';
                b += '2';
            } else if (s[i] == '1') {
                a += '0';
                b += '1';
            } else {
                a += '0';
                b += '0';
            }
        }

        cout << a << endl << b << endl;
    }
}
