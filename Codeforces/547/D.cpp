#include<bits/stdc++.h>
using namespace std;

int id(char c) {
    if (c == '?')
        return 26;
    else
        return (c - 'a');
}

int main() {
    int n;
    string l, r;
    bool paired[150003];
    vector<int> posL; //indices of question marks in l
    vector<int> posR[30]; //indices of each characters in r
    vector<pair<int, int> > answer;

    cin >> n >> l >> r;

    for (int i = 0; i < n; i++) {
        if (l[i] == '?') posL.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        posR[id(r[i])].push_back(i);
    }

    memset(paired, false, sizeof(paired));

    //pair each alphabet in l with alphabet/qmark in r
    for (int i = 0; i < n; i++) {
        if (l[i] == '?') continue;

        int match = -1;
        if (!posR[id(l[i])].empty())
            match = id(l[i]);

        if (match == -1 && !posR[26].empty())
            match = 26;

        if (match == -1)
            continue;

        int p = posR[match].back();

        paired[p] = true;
        answer.push_back({i, p});

        posR[match].pop_back();
    }

    //pair every unpaired character in r with question mark in l
    for (int i = 0; i < n; i++) {
        if (paired[i] == false) {
            if (!posL.empty()) {
                paired[i] = true;
                answer.push_back({posL.back(), i});

                posL.pop_back();
            }
        }
    }

    //pair each question mark in l with question mark in r
    while (!posL.empty() && !posR[26].empty()) {
        int p1 = posL.back();
        int p2 = posR[26].back();

        answer.push_back({p1, p2});
        posL.pop_back();
        posR[26].pop_back();
    }

    cout << (int) answer.size() << endl;
    for (int i = 0; i < (int) answer.size(); i++)
        cout << answer[i].first + 1 << " " << answer[i].second + 1 << endl;
}
