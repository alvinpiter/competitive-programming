#include<bits/stdc++.h>
using namespace std;
#define MAXN 400

int n, a, p[2 * MAXN + 3];
bool paired[2 * MAXN + 3];
vector<pair<int, pair<int, int> > > scores;

int main() {
    cin >> n;
    for (int i = 2; i <= 2 * n; i++) {
        for (int j = 1; j < i; j++) {
            cin >> a;
            scores.push_back({a, {i, j}});
        }
    }

    sort(scores.begin(), scores.end());

    memset(paired, false, sizeof(paired));
    for (int i = scores.size() - 1; i >= 0; i--) {
        int u = scores[i].second.first;
        int v = scores[i].second.second;

        if (paired[u] || paired[v]) {
            continue;
        } else {
            p[u] = v;
            p[v] = u;

            paired[u] = true;
            paired[v] = true;
        }
    }

    for (int i = 1; i <= 2 * n; i++)
        cout << p[i] << " ";
    cout << endl;
}
