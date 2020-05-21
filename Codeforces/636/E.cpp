#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

/*
We can divide path a-b-c into 4 parts: a-mid, mid-b, b-mid, mid-c
*/

int t, n, m, a, b, c, weight[MAXN + 3];
vector<int> adj[MAXN + 3];
LL weightSum[MAXN + 3], dist[3][MAXN + 3];

/*
who = 0 -> source is a
who = 1 -> source is b
who = 2 -> source is c
*/
void BFS(int who, int source) {
    for (int i = 1; i <= n; i++)
        dist[who][i] = -1;

    dist[who][source] = 0;

    queue<int> Q;
    Q.push(source);

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (auto v: adj[u]) {
            if (dist[who][v] == -1) {
                dist[who][v] = dist[who][u] + 1;
                Q.push(v);
            }
        }
    }
}

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);

        for (int i = 1; i <= n; i++)
            adj[i].clear();

        for (int i = 1; i <= m; i++)
            scanf("%d", &weight[i]);

        sort(weight + 1, weight + m + 1);

        weightSum[0] = 0;
        for (int i = 1; i <= m; i++)
            weightSum[i] = weightSum[i - 1] + weight[i];

        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        BFS(0, a); //BFS from a
        BFS(1, b); //BFS from b
        BFS(2, c); //BFS from c

        LL answer = 1e15;
        for (int mid = 1; mid <= n; mid++) {
            int cnt = dist[0][mid] + dist[1][mid] + dist[2][mid];
            int cntDouble = dist[1][mid];

            if (cnt > m)
                continue;

            LL cost = weightSum[cnt];
            cost += weightSum[cntDouble];

            answer = min(answer, cost);
        }

        cout << answer << endl;
    }
}
