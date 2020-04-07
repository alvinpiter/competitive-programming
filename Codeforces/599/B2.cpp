#include<bits/stdc++.h>
using namespace std;

int main() {
    int tc, n, cnt[26];
    string s, t;

    cin >> tc;
    for (int cases = 1; cases <= tc; cases++) {
        cin >> n;
        cin >> s >> t;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a'] += 1;
            cnt[t[i] - 'a'] += 1;
        }

        bool valid = true;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "No\n";
            continue;
        }

        vector<pair<int, int> > answer;
        for (int i = 0; i < n; i++) {
            if (s[i] != t[i]) {
                bool found = false;
                for (int j = i + 1; j < n; j++) {
                    if (s[j] == s[i]) {
                        found = true;

                        char tmp = s[j];
                        s[j] = t[i];
                        t[i] = tmp;

                        answer.push_back({j + 1, i + 1});

                        break;
                    }
                }

                if (!found) {
                    for (int j = i + 1; j < n; j++) {
                        if (t[j] == s[i]) {
                            found = true;

                            char tmp = t[j];
                            t[j] = s[j];
                            s[j] = tmp;

                            answer.push_back({j + 1, j + 1});

                            tmp = s[j];
                            s[j] = t[i];
                            t[i] = tmp;

                            answer.push_back({j + 1, i + 1});

                            break;
                        }
                    }
                }
            }
        }

        cout << "Yes\n";
        cout << answer.size() << endl;
        for (auto a: answer)
            cout << a.first << " " << a.second << endl;
    }
}
