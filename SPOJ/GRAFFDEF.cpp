#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define LL long long int

int N, M;
set<int> adj[MAXN + 3], btAdj[MAXN + 3]; //adj -> original adjacency list, btAdj -> bridge tree adjacency list
int currentDfsTime, dfsTime[MAXN + 3], minDfsTime[MAXN + 3];
bool visited[MAXN + 3];
vector<int> sizes; //Size of each bridge tree component

void DFS1(int u, int prv) {
    dfsTime[u] = ++currentDfsTime;
    minDfsTime[u] = dfsTime[u];

    for (auto v: adj[u]) {
        if (v == prv) continue;

        if (dfsTime[v] == -1) {
            DFS1(v, u);
            minDfsTime[u] = min(minDfsTime[u], minDfsTime[v]);

            if (minDfsTime[v] > dfsTime[u]) {
                //u-v is bridge, we removed it
                btAdj[u].erase(v);
                btAdj[v].erase(u);
            }
        } else {
            minDfsTime[u] = min(minDfsTime[u], dfsTime[v]);
        }
    }
}

int DFS2(int u) {
    visited[u] = true;

    int result = 1;
    for (auto v: btAdj[u]) {
        if (!visited[v]) {
            result += DFS2(v);
        }
    }

    return result;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].insert(v);
        adj[v].insert(u);

        btAdj[u].insert(v);
        btAdj[v].insert(u);
    }

    //Disconnect all bridges
    memset(dfsTime, -1, sizeof(dfsTime));
    currentDfsTime = 0;
    DFS1(1, 1);

    //Count number of nodes in bridge-tree component
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            sizes.push_back(DFS2(i));
        }
    }

    LL allCount = ((LL) N * N - N)/2;
    LL winCount = 0;
    for (auto size: sizes)
        winCount += ((LL) size * size - size)/2;

    LL loseCount = allCount - winCount;
    double loseProbability = (1.0 * loseCount)/allCount;

    printf("%.5lf\n", loseProbability);
}
