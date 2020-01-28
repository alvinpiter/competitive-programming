#include<bits/stdc++.h>
using namespace std;
#define MAXN 1500
#define MAXM 5000
#define MOD 1000000007
#define LL long long int

int N, M, origin[MAXM + 3], destination[MAXM + 3], len[MAXM + 3], dist[MAXN + 3];
LL comingIn[MAXN + 3], goingOut[MAXN + 3], answer[MAXM + 3];
vector<pair<int, int> > neighbor[MAXN + 3], revNeighbor[MAXN + 3];

void dijkstra(int start) {
    for (int i = 1; i <= N; i++)
        dist[i] = MOD;

    priority_queue<pair<int, int> > pq;

    dist[start] = 0;
    pq.push(make_pair(-dist[start], start));

    while (!pq.empty()) {
        pair<int, int> top = pq.top(); pq.pop();

        int u = top.second;
        for (int i = 0; i < neighbor[u].size(); i++) {
            int v = neighbor[u][i].first;
            int cost = neighbor[u][i].second;

            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                pq.push(make_pair(-dist[v], v));
            }
        }
    }
}

LL countComingIn(int v) {
    if (comingIn[v] != -1)
        return comingIn[v];

    comingIn[v] = 0;
    for (int i = 0; i < revNeighbor[v].size(); i++) {
        int u = revNeighbor[v][i].first;
        int cost = revNeighbor[v][i].second;

        if (dist[u] + cost == dist[v])
            comingIn[v] = (comingIn[v] + countComingIn(u))%MOD;
    }

    return comingIn[v];
}

LL countGoingOut(int u) {
    if (goingOut[u] != -1)
        return goingOut[u];

    goingOut[u] = 0;
    for (int i = 0; i < neighbor[u].size(); i++) {
        int v = neighbor[u][i].first;
        int cost = neighbor[u][i].second;

        if (dist[v] == dist[u] + cost)
            goingOut[u] = (goingOut[u] + 1 + countGoingOut(v))%MOD;
    }

    return goingOut[u];
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        cin >> origin[i] >> destination[i] >> len[i];

        neighbor[origin[i]].push_back(make_pair(destination[i], len[i]));
        revNeighbor[destination[i]].push_back(make_pair(origin[i], len[i]));
    }

    memset(answer, 0, sizeof(answer));
    for (int start = 1; start <= N; start++) {
        memset(comingIn, -1, sizeof(comingIn));
        memset(goingOut, -1, sizeof(goingOut));

        dijkstra(start);

        comingIn[start] = 1;
        for (int i = 1; i <= M; i++) {
            int u = origin[i];
            int v = destination[i];
            int l = len[i];

            if (dist[v] == dist[u] + l) {
                LL ways = (countComingIn(u) * (1 + countGoingOut(v)))%MOD;
                answer[i] = (answer[i] + ways)%MOD;
            }
        }
    }

    for (int i = 1; i <= M; i++)
        cout << answer[i] << endl;
}
