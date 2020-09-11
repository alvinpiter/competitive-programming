//Can be solved with dp too.

#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define INF 1000000000

int n, a[MAXN + 3], b[MAXN + 3], c, dist[MAXN + 3][2];

int main() {
    scanf("%d%d", &n, &c);
    for (int i = 1; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i < n; i++)
        scanf("%d", &b[i]);

    for (int i = 1; i <= n; i++)
        dist[i][0] = dist[i][1] = INF;

    dist[1][0] = 0;
    priority_queue<pair<int, pair<int, int> > > pq;
    pq.push(make_pair(-dist[1][0], make_pair(1, 0)));

    while (!pq.empty()) {
        pair<int, pair<int, int> > top = pq.top(); pq.pop();
        int u = top.second.first;
        int last = top.second.second; //last = 0 -> stair, last = 1 -> elevator

        //Go to the next floor by stair
        if (u + 1 <= n && dist[u + 1][0] > dist[u][last] + a[u]) {
            dist[u + 1][0] = dist[u][last] + a[u];
            pq.push({-dist[u + 1][0], {u + 1, 0}});
        }

        //Go to the next floor by elevator
        if (u + 1 <= n && dist[u + 1][1] > dist[u][last] + b[u] + (last == 1 ? 0 : c)) {
            dist[u + 1][1] = dist[u][last] + b[u] + (last == 1 ? 0 : c);
            pq.push({-dist[u + 1][1], {u + 1, 1}});
        }
    }

    for (int i = 1; i <= n; i++)
        cout << min(dist[i][0], dist[i][1]) << " ";
    cout << endl;
}
