#include<bits/stdc++.h>
using namespace std;

int t, n, m;
string strings[12];

int diffCount(string s, string t) {
    int cnt = 0;
    for (int i = 0; i < (int) s.length(); i++) {
        if (s[i] != t[i])
            cnt += 1;
    }

    return cnt;
}

//check if s differs at most 1 position with every string in strings.
bool validate(string s) {
    for (int i = 0; i < n; i++) {
        if (diffCount(s, strings[i]) > 1)
            return false;
    }

    return true;
}

int main() {

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            cin >> strings[i];

        if (validate(strings[0])) {
            cout << strings[0] << endl;
            continue;
        }

        bool found = false;
        for (int i = 0; i < m && !found; i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == strings[0][i])
                    continue;

                string newString = strings[0].substr(0, i) + c + strings[0].substr(i + 1);
                if (validate(newString)) {
                    cout << newString << endl;
                    found = true;
                    break;
                }
            }
        }

        if (!found)
            cout << -1 << endl;
    }
}
