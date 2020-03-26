#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    vector<int> pos[26];

    cin >> s;
    for (int i = 0; i < s.length(); i++)
        pos[s[i] - 'a'].push_back(i);

    int lastPos = -1;
    string answer = "";

    while (true) {
        int nextChar = -1;
        for (int c = 25; c >= 0; c--) {
            int idx = lower_bound(pos[c].begin(), pos[c].end(), lastPos + 1) - pos[c].begin();
            if (idx < pos[c].size()) {
                nextChar = c;
                lastPos = pos[c][idx];
                break;
            }
        }

        if (nextChar == -1)
            break;
        else
            answer += (char) (nextChar + 'a');
    }

    cout << answer << endl;
}
