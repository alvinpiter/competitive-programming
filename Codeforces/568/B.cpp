#include<bits/stdc++.h>
using namespace std;

vector<pair<char, int> > compress(string s) {
    vector<pair<char, int> > result;

    result.push_back({s[0], 1});
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == s[i - 1]) {
            result.back().second += 1;
        } else {
            result.push_back({s[i], 1});
        }
    }

    return result;
}

int main() {
    int n;
    string s, t;

    cin >> n;
    for (int cases = 1; cases <= n; cases++) {
        cin >> s >> t;

        vector<pair<char, int> > compressedS = compress(s);
        vector<pair<char, int> > compressedT = compress(t);

        bool valid = true;

        if (compressedS.size() != compressedT.size())
            valid = false;

        for (int i = 0; i < min(compressedS.size(), compressedT.size()); i++) {
            if (compressedS[i].first != compressedT[i].first)
                valid = false;

            if (compressedS[i].second > compressedT[i].second)
                valid = false;
        }

        if (valid)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
