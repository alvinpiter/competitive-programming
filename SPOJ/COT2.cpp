#include<bits/stdc++.h>
using namespace std;
#define MAXN 40000
#define MAXM 100000
#define MAXLG 17
#define BLOCKSIZE 300

struct Query {
    int index, l, r, lca;

    Query(int _index, int _l, int _r, int _lca): index(_index), l(_l), r(_r), lca(_lca) {};
};

bool queryComparator(Query a, Query b) {
    if (a.l/BLOCKSIZE != b.l/BLOCKSIZE)
        return a.l/BLOCKSIZE < b.l/BLOCKSIZE;
    else
        return a.r < b.r;
}

int N, M, weights[MAXN + 3], answer[MAXM + 3];
vector<int> uniqWeights;

//DFS ordering variables
int dfsTime, tin[MAXN + 3], tout[MAXN + 3], id[2 * MAXN + 3];
vector<int> adj[MAXN + 3];

//LCA variables
int P[MAXN + 3][MAXLG + 3], depth[MAXN + 3];

/*
Mo's variables
nodeFreq[i] -> How many times node i appears in current window. Possible values are 0, 1, or 2.
Whenever a node appears even number of time, we don't consider the value frequency.
*/
vector<Query> queries;
int nodeFreq[MAXN + 3], valueFreq[MAXN + 3], currentL, currentR, currentCounter;

void DFS(int u, int prv) {
    dfsTime += 1;
    tin[u] = dfsTime;
    id[dfsTime] = u;

    for (auto v: adj[u]) {
        if (v != prv) {
            P[v][0] = u;
            depth[v] = depth[u] + 1;
            DFS(v, u);
        }
    }

    dfsTime += 1;
    tout[u] = dfsTime;
    id[dfsTime] = u;
}

int LCA(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);

    int diff = depth[v] - depth[u];
    for (int lg = 0; lg <= MAXLG; lg++) {
        if (diff & (1 << lg))
            v = P[v][lg];
    }

    if (u == v)
        return u;

    for (int lg = MAXLG; lg >= 0; lg--) {
        if (P[u][lg] != P[v][lg]) {
            u = P[u][lg];
            v = P[v][lg];
        }
    }

    return P[u][0];
}

//Add a node to Mo's window
void add(int id) {
    nodeFreq[id] += 1;
    if (nodeFreq[id] == 1) {
        valueFreq[weights[id]] += 1;
        if (valueFreq[weights[id]] == 1)
            currentCounter += 1;
    } else {
        valueFreq[weights[id]] -= 1;
        if (valueFreq[weights[id]] == 0)
            currentCounter -= 1;
    }
}

//Delete a node from Mo's window
void del(int id) {
    nodeFreq[id] -= 1;
    if (nodeFreq[id] == 0) {
        valueFreq[weights[id]] -= 1;
        if (valueFreq[weights[id]] == 0)
            currentCounter -= 1;
    } else {
        valueFreq[weights[id]] += 1;
        if (valueFreq[weights[id]] == 1)
            currentCounter += 1;
    }
}

void processQueries() {
    sort(queries.begin(), queries.end(), queryComparator);

    memset(nodeFreq, 0, sizeof(nodeFreq));
    memset(valueFreq, 0, sizeof(valueFreq));

    currentL = queries[0].l;
    currentR = currentL - 1;
    currentCounter = 0;

    for (auto query: queries) {
        int index = query.index;
        int l = query.l;
        int r = query.r;
        int lca = query.lca;

        while (currentL < l) {
            del(id[currentL++]);
        }

        while (currentL > l) {
            add(id[--currentL]);
        }

        while (currentR < r) {
            add(id[++currentR]);
        }

        while (currentR > r) {
            del(id[currentR--]);
        }

        if (lca != -1) add(id[lca]);

        answer[index] = currentCounter;

        if (lca != -1) del(id[lca]);
    }

    for (int i = 1; i <= M; i++)
        printf("%d\n", answer[i]);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &weights[i]);

        uniqWeights.push_back(weights[i]);
    }

    for (int i = 1; i <= N - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(P, -1, sizeof(P));

    dfsTime = 0;
    depth[1] = 0;
    DFS(1, 1);

    //Init P
    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            if (P[i][lg - 1] != -1)
                P[i][lg] = P[P[i][lg - 1]][lg - 1];
        }
    }

    //Normalize weights
    sort(uniqWeights.begin(), uniqWeights.end());
    uniqWeights.resize(distance(uniqWeights.begin(), unique(uniqWeights.begin(), uniqWeights.end())));
    for (int i = 1; i <= N; i++)
        weights[i] = (lower_bound(uniqWeights.begin(), uniqWeights.end(), weights[i]) - uniqWeights.begin()) + 1;

    for (int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (tin[u] > tin[v]) swap(u, v);

        int lca = LCA(u, v);

        if (lca == u) {
            queries.push_back(Query(i, tin[u], tin[v], -1));
        } else {
            queries.push_back(Query(i, tout[u], tin[v], tin[lca]));
        }
    }

    if (M > 0)
        processQueries();
}

/*
8 1
2 3 1 2 1 1 1 2
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 8
*/
