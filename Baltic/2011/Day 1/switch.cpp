#include<bits/stdc++.h>
using namespace std;
#define INF 1000000
#define MAXV 260000

int N, M, V, dist[MAXV + 3];
vector<pair<int, int> > adj[MAXV + 3];

int main() {
    cin >> N >> M;

    V = (N + 1)*(M + 1);
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= M; c++) {
            char sign;
            cin >> sign;

            int topLeft = (r - 1)*(M + 1) + c;
            int topRight = topLeft + 1;
            int bottomLeft = r*(M + 1) + c;
            int bottomRight = bottomLeft + 1;
            int costTopLeftBottomRight, costTopRightBottomLeft;

            if (sign == '\\') {
                costTopLeftBottomRight = 0;
                costTopRightBottomLeft = 1;
            } else {
                costTopLeftBottomRight = 1;
                costTopRightBottomLeft = 0;
            }

            adj[topLeft].push_back({bottomRight, costTopLeftBottomRight});
            adj[bottomRight].push_back({topLeft, costTopLeftBottomRight});

            adj[topRight].push_back({bottomLeft, costTopRightBottomLeft});
            adj[bottomLeft].push_back({topRight, costTopRightBottomLeft});
        }
    }

    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
    }

    dist[1] = 0;

    priority_queue<pair<int, int> > pq;
    pq.push({-dist[1], 1});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int u = top.second;

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int cost = adj[u][i].second;

            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                pq.push({-dist[v], v});
            }
        }
    }

    if (dist[V] < INF)
        cout << dist[V] << endl;
    else
        cout << "NO SOLUTION\n";
}

/*
3 5
\\/\\
\\///
/\\\\
*/
