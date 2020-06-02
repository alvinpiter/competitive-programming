#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, m, dist[MAXN + 3];
vector<pair<int, char> > adj[MAXN + 3];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        char c[2];

        scanf("%d%d%s", &u, &v, c);

        adj[u].push_back({v, c[0]});
        adj[v].push_back({u, c[0]});
    }

    for (int i = 1; i <= n; i++) {
        dist[i] = MAXN;
    }

    dist[n] = 0;

    queue<int> q;
    q.push(n);
    dist[n] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e: adj[u]) {
            int v = e.first;
            if (dist[v] == MAXN) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    vector<char> labels;
    vector<int> actives;
    actives.push_back(1);

    bool done[MAXN + 3];
    memset(done, false, sizeof(done));
    done[1] = true;

    int prv[MAXN + 3];

    //traverse layer by layer
    for (int rep = 1; rep <= dist[1]; rep++) {
        char minChar = 'z';
        for (auto u: actives) {
            for (auto e: adj[u]) {
                int v = e.first;
                char label = e.second;

                if (dist[v] == dist[u] - 1)
                    minChar = min(minChar, label);
            }
        }

        labels.push_back(minChar);

        vector<int> tempActives;

        for (auto u: actives) {
            for (auto e: adj[u]) {
                int v = e.first;
                char label = e.second;

                if (dist[v] == dist[u] - 1 && label == minChar && !done[v]) {
                    done[v] = true;
                    prv[v] = u;
                    tempActives.push_back(v);
                }
            }
        }

        actives = tempActives;
    }

    vector<int> vertices;

    int current = n;
    vertices.push_back(current);

    while (current != 1) {
        current = prv[current];
        vertices.push_back(current);
    }

    reverse(vertices.begin(), vertices.end());

    printf("%d\n", dist[1]);
    for (auto v: vertices)
        printf("%d ", v);
    printf("\n");
    for (auto l: labels)
        printf("%c", l);
    printf("\n");
}

/*
4 4
1 2 a
1 3 a
2 4 b
3 4 c

5 4
1 2 b
3 4 a
2 5 a
4 5 a

7 7
1 2 a
2 3 a
3 4 a
4 5 b
4 6 b
5 7 c
6 7 d
*/
