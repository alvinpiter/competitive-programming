#include<bits/stdc++.h>
using namespace std;

int t, n, ans;
string s, mini;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> s;

        mini = s;
        ans = 1;
        for (int len = 2; len < n; len++) {
            int numReverse = n - len + 1;
            string a = s.substr(len - 1);
            string b = s.substr(0, len - 1);
            if (numReverse % 2 == 1)
                reverse(b.begin(), b.end());

            string temp = a + b;
            if (temp < mini) {
                mini = temp;
                ans = len;
            }
        }

        reverse(s.begin(), s.end());
        if (s < mini) {
            mini = s;
            ans = n;
        }

        cout << mini << endl;
        cout << ans << endl;
    }
}
