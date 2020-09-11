#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    bool removed[400003];
    string s;
    vector<int> pos[26];

    cin >> n >> k;
    cin >> s;

    for (int i = 0; i < n; i++) {
        pos[s[i] - 'a'].push_back(i);
    }

    memset(removed, false, sizeof(removed));
    for (int c = 0; c < 26 && k > 0; c++) {
        for (int i = 0; i < pos[c].size() && k > 0; i++) {
            removed[pos[c][i]] = true;
            k -= 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (removed[i])
            continue;
        else
            cout << s[i];
    }
    cout << endl;
}
