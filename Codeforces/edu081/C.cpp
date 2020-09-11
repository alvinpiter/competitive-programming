#include<bits/stdc++.h>
using namespace std;

int T;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        string s, t;
        cin >> s >> t;

        vector<int> pos[26];
        for (int i = 0; i < s.length(); i++)
            pos[s[i] - 'a'].push_back(i);

        int answer = 1;
        int sIndex = 0;
        bool possible = true;
        for (int i = 0; i < t.length();) {
            int charIndex = t[i] - 'a';
            if (pos[charIndex].empty()) {
                possible = false;
                break;
            }

            int p = lower_bound(pos[charIndex].begin(), pos[charIndex].end(), sIndex) - pos[charIndex].begin();
            if (p < pos[charIndex].size()) {
                sIndex = pos[charIndex][p] + 1;
                i++;
            } else {
                answer += 1;
                sIndex = 0;
            }
        }

        if (possible)
            cout << answer << endl;
        else
            cout << -1 << endl;
    }
}
