#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m, direction; //direction = {0, 1} = {right, down}
    vector<pair<int, int> > pos;

    cin >> n;

    pos.push_back({1, 1});
    m = 1;
    direction = 0;

    while ((int) pos.size() < n) {
        int r = pos.back().first;
        int c = pos.back().second;

        if (direction == 0)
            c += 1;
        else
            r += 1;

        pos.push_back({r, c});
        m = max(m, max(r, c));
        direction = 1 - direction;
    }

    cout << m << endl;
    for (auto p: pos)
        cout << p.first << " " << p.second << endl;
}
