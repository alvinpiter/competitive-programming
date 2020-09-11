#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, p[MAXN + 3], answer[MAXN + 3];
int dfsTime, tin[MAXN + 3], tout[MAXN + 3];
int bit[MAXN + 3];
vector<int> children[MAXN + 3];

void update(int idx, int val) {
    while (idx <= N) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

void DFS(int u) {
    tin[u] = ++dfsTime;
    for (auto v: children[u]) {
        DFS(v);
    }

    tout[u] = dfsTime;
}

int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> p[i];

    for (int i = 2; i <= N; i++) {
        int par;
        cin >> par;

        children[par].push_back(i);
    }

    dfsTime = 0;
    DFS(1);

    vector<pair<int, int> > sortedP;
    for (int i = 1; i <= N; i++) {
        sortedP.push_back({p[i], i});
    }

    sort(sortedP.begin(), sortedP.end());
    reverse(sortedP.begin(), sortedP.end());

    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < N; i++) {
        int idx = sortedP[i].second;
        answer[idx] = query(tout[idx]) - query(tin[idx] - 1);
        update(tin[idx], 1);
    }

    for (int i = 1; i <= N; i++) {
        cout << answer[i] << endl;
    }
}
