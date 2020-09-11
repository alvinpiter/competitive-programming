#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int parent[MAXN + 3], sz[MAXN + 3];
int n, m;
LL answer[MAXN + 3];
vector<pair<int, pair<int ,int> > > edges;
vector<pair<int, int> > queries;

int findSet(int u) {
    return (u == parent[u] ? u : parent[u] = findSet(parent[u]));
}

//Returns number of created connections
LL joinSet(int u, int v) {
    int pu = findSet(u);
    int pv = findSet(v);
    LL result = (LL) sz[pu] * sz[pv];

    parent[pu] = pv;
    sz[pv] += sz[pu];

    return result;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        edges.push_back({w, {u, v}});
    }

    for (int i = 1; i <= m; i++) {
        int q;
        scanf("%d", &q);

        queries.push_back({q, i});
    }

    sort(edges.begin(), edges.end());
    sort(queries.begin(), queries.end());

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    memset(answer, 0, sizeof(answer));

    int ptr = 0;
    for (int i = 0; i < queries.size(); i++) {
        while (ptr < edges.size() && edges[ptr].first <= queries[i].first) {
            int u = edges[ptr].second.first;
            int v = edges[ptr].second.second;

            answer[queries[i].second] += joinSet(u, v);

            ptr += 1;
        }

        if (i > 0)
            answer[queries[i].second] += answer[queries[i - 1].second];
    }

    for (int i = 1; i <= m; i++)
        printf("%lld ", answer[i]);
    printf("\n");
}
