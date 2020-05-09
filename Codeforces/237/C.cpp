#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int n, k, degree[MAXN + 3];
vector<int> who[MAXN + 3];
vector<pair<int, int> > edges;

int main() {
    scanf("%d%d", &n, &k);

    int minD = n;
    int maxD = 0;
    for (int i = 1; i <= n; i++) {
        int d;
        scanf("%d", &d);

        who[d].push_back(i);
        minD = min(minD, d);
        maxD = max(maxD, d);
    }

    //make sure there is no gap
    for (int d = minD; d <= maxD; d++) {
        if (who[d].empty()) {
            printf("-1\n");
            return 0;
        }
    }

    //make sure there is exactly 1 node with d = 0
    if (who[0].size() != 1) {
        printf("-1\n");
        return 0;
    }

    memset(degree, 0, sizeof(degree));

    //construct solution
    set<int> active;
    active.insert(who[0][0]);
    for (int d = 1; d <= maxD; d++) {
        for (auto v: who[d]) {
            //all previous nodes are "full"
            if (active.empty()) {
                printf("-1\n");
                return 0;
            }

            int u = *(active.begin());
            edges.push_back({u, v});
            degree[u] += 1;
            degree[v] += 1;

            if (degree[u] == k)
                active.erase(u);
        }

        active.clear();
        for (auto v: who[d]) {
            if (degree[v] < k)
                active.insert(v);
        }
    }

    printf("%d\n", (int) edges.size());
    for (auto edge: edges)
        printf("%d %d\n", edge.first, edge.second);
}
