#include<bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        string s;
        cin >> s;

        if (s.length() == 1) {
            cout << "YES\n";
            cout << s[0];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c != s[0])
                    cout << c;
            }
            cout << endl;

            continue;
        }

        set<int> neighbor[26]; //neighbor[i] = neighbor of character i
        for (int i = 0; i < s.length(); i++) {
            if (i > 0) {
                neighbor[s[i] - 'a'].insert(s[i - 1] - 'a');
                neighbor[s[i - 1] - 'a'].insert(s[i] - 'a');
            }

            if (i < s.length() - 1) {
                neighbor[s[i] - 'a'].insert(s[i + 1] - 'a');
                neighbor[s[i + 1] - 'a'].insert(s[i] - 'a');
            }
        }

        bool valid = true;

        vector<int> charWithOneNeighbor;
        for (int i = 0; i < 26; i++) {
            if (neighbor[i].size() == 1)
                charWithOneNeighbor.push_back(i);

            if (neighbor[i].size() > 2)
                valid = false;
        }

        if (!valid || charWithOneNeighbor.size() != 2) {
            cout << "NO\n";
            continue;
        } else {
            string answer = "";
            int current = charWithOneNeighbor[0];

            bool seen[26];
            memset(seen, false, sizeof(seen));
            while (true) {
                answer += (char) (current + 'a');
                seen[current] = true;

                int first = *neighbor[current].begin();
                int second = *neighbor[current].rbegin();
                if (!seen[first])
                    current = first;
                else if (!seen[second])
                    current = second;
                else
                    break;
            }

            for (int i = 0; i < 26; i++) {
                if (!seen[i])
                    answer += (char) (i + 'a');
            }

            cout << "YES\n";
            cout << answer << endl;
        }
    }
}
