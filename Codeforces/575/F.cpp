#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e15
#define MAXK 400

/*
Observation:
Only consider the k smallest edges and construct new graph from it.
This graph will have at most 2*k vertices. Run Floyd-Warshall's afterward.

Why is this true?
Because using these k smallest edges we can have at least k smallest shortest path.
*/

int n, m, k, N;
LL dist[2 * MAXK + 3][2 * MAXK + 3];
vector<int> uniqV;
vector<pair<int, pair<int, int> > > edges;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        edges.push_back({w, {u, v}});
    }

    sort(edges.begin(), edges.end());
    for (int i = 0; i < min(k, (int) edges.size()); i++) {
        uniqV.push_back(edges[i].second.first);
        uniqV.push_back(edges[i].second.second);
    }

    sort(uniqV.begin(), uniqV.end());
    uniqV.resize(distance(uniqV.begin(), unique(uniqV.begin(), uniqV.end())));

    N = uniqV.size();
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }

    for (int i = 0; i < min(k, (int) edges.size()); i++) {
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        u = lower_bound(uniqV.begin(), uniqV.end(), u) - uniqV.begin();
        v = lower_bound(uniqV.begin(), uniqV.end(), v) - uniqV.begin();

        u += 1;
        v += 1;

        dist[u][v] = dist[v][u] = edges[i].first;
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }

    vector<LL> sp;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++)
            sp.push_back(dist[i][j]);
    }

    sort(sp.begin(), sp.end());

    printf("%lld\n", sp[k - 1]);
}
