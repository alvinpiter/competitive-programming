#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

string s;
int q, match[MAXN + 3]; //match[i] = smallest index j such that sj = pi
vector<int> pos[26]; //pos[i] -> indices of character i in s
vector<char> p;

int main() {
    cin >> s;

    for (int i = 0; i < (int) s.length(); i++) {
        pos[s[i] - 'a'].push_back(i);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        string op;
        cin >> op;

        if (op == "push") {
            string c;
            cin >> c;

            int lastMatch = (p.empty() ? -1 : match[(int) p.size() - 1]);

            p.push_back(c[0]);
            if (lastMatch < (int) s.length()) {
                int charIdx = c[0] - 'a';
                int position = lower_bound(pos[charIdx].begin(), pos[charIdx].end(), lastMatch + 1) - pos[charIdx].begin();

                if (position == (int) pos[charIdx].size())
                    match[(int) p.size() - 1] = (int) s.length();
                else
                    match[(int) p.size() - 1] = pos[charIdx][position];
            } else {
                match[(int) p.size() - 1] = (int) s.length();
            }
        } else {
            p.pop_back();
        }

        if (match[(int) p.size() - 1] < s.length())
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
