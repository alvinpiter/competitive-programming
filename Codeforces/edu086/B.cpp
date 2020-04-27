#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, cnt0, cnt1;
    string s;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> s;

        cnt0 = cnt1 = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '0')
                cnt0 += 1;
            else
                cnt1 += 1;
        }

        if (cnt0 == 0 || cnt1 == 0)
            cout << s << endl;
        else {
            //match all the zeros
            for (int i = 1; i <= cnt0; i++)
                cout << 0 << 1;

            //match all the ones
            for (int i = 1; i <= cnt1; i++)
                cout << 0 << 1;

            cout << endl;
        }
    }
}
