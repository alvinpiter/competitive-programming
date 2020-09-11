#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define LL long long int

LL value[MAXN + 3]; //Value of a node excluding pending subtree update of it's ancestors
LL sum[MAXN + 3]; //Sum of all values under this subtree including pending subtree update below it
LL pending[MAXN + 3]; //Pending subtree update
int sz[MAXN + 3]; //Size of subtree

int N, Q, P[MAXN + 3];
vector<int> children[MAXN + 3], ancestors[MAXN + 3];

//O(N)
void DFS(int u, int prev) {
    sz[u] = 1;
    sum[u] = value[u];
    for (int i = 0; i < children[u].size(); i++) {
        int v = children[u][i];
        DFS(v, u);

        sz[u] += sz[v];
        sum[u] += sum[v];
    }
}

//O(ND)
void fillAncestors() {
    for (int i = 1; i <= N; i++) {
        int current = i;
        while (current != -1) {
            ancestors[i].push_back(current);
            current = P[current];
        }
    }
}

//O(D^2)
int getLCA(int u, int v) {
    for (int i = 0; i < ancestors[u].size(); i++) {
        for (int j = 0; j < ancestors[v].size(); j++) {
            if (ancestors[u][i] == ancestors[v][j])
                return ancestors[u][i];
        }
    }
}

//O(D)
LL aggregateNodeValue(int u) {
    LL result = value[u];
    for (int i = 0; i < ancestors[u].size(); i++)
        result += pending[ancestors[u][i]];

    return result;
}

//O(D^2)
void query1(int u, int v, int x) {
    int lca = getLCA(u, v);

    for (int i = 0; i < ancestors[u].size(); i++) {
        int current = ancestors[u][i];
        value[current] += x;

        for (int j = 0; j < ancestors[current].size(); j++)
            sum[ancestors[current][j]] += x;

        if (current == lca)
            break;
    }

    for (int i = 0; i < ancestors[v].size(); i++) {
        int current = ancestors[v][i];
        value[current] += x;

        for (int j = 0; j < ancestors[current].size(); j++)
            sum[ancestors[current][j]] += x;

        if (current == lca)
            break;
    }

    value[lca] -= x;
    for (int i = 0; i < ancestors[lca].size(); i++)
        sum[ancestors[lca][i]] -= x;
}

//O(D)
void query2(int u, int x) {
    pending[u] += x;

    LL sumAddition = (LL) sz[u] * x;
    for (int i = 0; i < ancestors[u].size(); i++)
        sum[ancestors[u][i]] += sumAddition;
}

//O(D^2)
LL query3(int u, int v) {
    LL result = 0;
    int lca = getLCA(u, v);

    for (int i = 0; i < ancestors[u].size(); i++) {
        result += aggregateNodeValue(ancestors[u][i]);
        if (ancestors[u][i] == lca)
            break;
    }

    for (int i = 0; i < ancestors[v].size(); i++) {
        result += aggregateNodeValue(ancestors[v][i]);
        if (ancestors[v][i] == lca)
            break;
    }

    result -= aggregateNodeValue(lca);

    return result;
}

//O(D)
LL query4(int u) {
    LL totalPendingUpdate = 0;
    for (int i = 1; i < ancestors[u].size(); i++)
        totalPendingUpdate += pending[ancestors[u][i]];

    return sum[u] + totalPendingUpdate * sz[u];
}

int main() {
    cin >> N >> Q;
    P[1] = -1;
    for (int i = 2; i <= N; i++) {
        cin >> P[i];
        children[P[i]].push_back(i);
    }

    for (int i = 1; i <= N; i++)
        cin >> value[i];

    DFS(1, 1);
    fillAncestors();
    memset(pending, 0, sizeof(pending));

    for (int i = 1; i <= Q; i++) {
        int typ, U, V, X;

        cin >> typ;
        if (typ == 1) {
            cin >> U >> V >> X;
            query1(U, V, X);
        } else if (typ == 2) {
            cin >> U >> X;
            query2(U, X);
        } else if (typ == 3) {
            cin >> U >> V;
            cout << query3(U, V) << endl;
        } else {
            cin >> U;
            cout << query4(U) << endl;
        }
    }
}
