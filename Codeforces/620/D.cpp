#include<bits/stdc++.h>
using namespace std;

int t, n;
string s;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> s;

        vector<int> best;
        for (int i = 1; i <= n; i++)
            best.push_back(i);

        vector<int> worst;
        for (int i = n; i >= 1; i--)
            worst.push_back(i);

        vector<pair<int, int> > bestReverses;
        for (int i = 0; i < s.length(); ) {
            if (s[i] == '<') {
                i += 1;
                continue;
            }

            int j = i;
            while (j < s.length() && s[j] == '>')
                j += 1;

            bestReverses.push_back({i, j});
            i = j;
        }

        for (auto p: bestReverses) {
            reverse(best.begin() + p.first, best.begin() + p.second + 1);
        }

        vector<pair<int, int> > worstReverses;
        for (int i = 0; i < s.length(); ) {
            if (s[i] == '>') {
                i += 1;
                continue;
            }

            int j = i;
            while (j < s.length() && s[j] == '<')
                j += 1;

            worstReverses.push_back({i, j});
            i = j;
        }

        for (auto p: worstReverses) {
            reverse(worst.begin() + p.first, worst.begin() + p.second + 1);
        }

        for (int i = 0; i < (int) worst.size(); i++) {
            if (i > 0) cout << " ";
            cout << worst[i];
        }
        cout << endl;

        for (int i = 0; i < (int) best.size(); i++) {
            if (i > 0) cout << " ";
            cout << best[i];
        }
        cout << endl;
    }
}
