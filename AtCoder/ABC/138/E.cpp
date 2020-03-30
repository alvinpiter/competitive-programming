#include<bits/stdc++.h>
using namespace std;
#define LL long long int

string s, t;
vector<int> pos[26];
int ptr[26], numS;

int main() {
    cin >> s >> t;

    for (int i = 0; i < s.length(); i++) {
        pos[s[i] - 'a'].push_back(i);
    }

    numS = 0;
    int lastIndex = -1;
    LL answer;
    for (int i = 0; i < t.length(); i++) {
        int charIndex = (t[i] - 'a');

        if (pos[charIndex].size() == 0) {
            cout << "-1\n";
            return 0;
        }

        int p = lower_bound(pos[charIndex].begin(), pos[charIndex].end(), lastIndex + 1) - pos[charIndex].begin();
        if (p == pos[charIndex].size()) {
            numS += 1;
            lastIndex = pos[charIndex][0];
        } else {
            lastIndex = pos[charIndex][p];
        }

        answer = (LL) numS * (LL) s.length() + lastIndex + 1;
    }

    cout << answer << endl;
}
