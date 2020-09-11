#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, lastR, maxi;
    string s;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> s;
        s = "R" + s + "R";

        maxi = 0;
        lastR = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'R') {
                maxi = max(maxi, i - lastR);
                lastR = i;
            }
        }

        cout << maxi << endl;
    }

}
