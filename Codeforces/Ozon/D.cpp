#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int n;
set<int> adj[MAXN + 3];
set<int> leaves;

void answer(int u) {
    cout << "! " << u << endl;
    cout.flush();
}

void ask(int u, int v) {
    cout << "? " << u << " " << v << endl;
    cout.flush();
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].insert(v);
        adj[v].insert(u);
    }

    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 1)
            leaves.insert(i);
    }

    while (true) {
        if (leaves.size() == 1) {
            int root = *(leaves.begin());
            answer(root);
            break;
        }

        int u = *(leaves.begin());
        int v = *(leaves.rbegin());
        int lca;

        ask(u, v);

        cin >> lca;
        if (lca == u || lca == v) {
            answer(lca);
            break;
        } else {
            leaves.erase(u);
            int neighborU = *(adj[u].begin());
            adj[u].erase(neighborU);
            adj[neighborU].erase(u);
            if (adj[neighborU].size() == 1)
                leaves.insert(neighborU);

            leaves.erase(v);
            int neighborV = *(adj[v].begin());
            adj[v].erase(neighborV);
            adj[neighborV].erase(v);
            if (adj[neighborV].size() == 1)
                leaves.insert(neighborV);
        }
    }
}
