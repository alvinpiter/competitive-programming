#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

vector<int> adj[MAXN + 3], revAdj[MAXN + 3], shrinkAdj[MAXN + 3];
stack<int> order;
int N, M;
int numScc, sccOf[MAXN + 3], inDegree[MAXN + 3];
bool visited[MAXN + 3];
vector<int> sources; //node in shrinked graph with zero indegree

void DFS1(int u) {
    visited[u] = true;
    for (auto v: revAdj[u]) {
        if (visited[v] == false)
            DFS1(v);
    }

    order.push(u);
}

void DFS2(int u) {
    visited[u] = true;
    sccOf[u] = numScc;
    for (auto v: adj[u]) {
        if (visited[v] == false)
            DFS2(v);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        revAdj[v].push_back(u);
    }

    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= N; i++) {
        if (visited[i] == false) {
            DFS1(i);
        }
    }

    memset(visited, false, sizeof(visited));
    numScc = 0;
    while (!order.empty()) {
        int u = order.top(); order.pop();

        if (visited[u])
            continue;

        numScc += 1;
        DFS2(u);
    }

    //Shrink the graph (make it DAG). Also calculate inDegree for each SCC
    memset(inDegree, 0, sizeof(inDegree));
    for (int u = 1; u <= N; u++) {
        for (auto v: adj[u]) {
            int uu = sccOf[u];
            int vv = sccOf[v];
            if (uu != vv) {
                shrinkAdj[uu].push_back(vv);
                inDegree[vv] += 1;
            }
        }
    }

    for (int u = 1; u <= numScc; u++) {
        if (inDegree[u] == 0)
            sources.push_back(u);
    }

    bool valid = true;
    for (int i = 1; i <= numScc; i++) {
        int sz = sources.size();
        if (sz > 1) {
            valid = false;
            break;
        }

        vector<int> temp(sources);
        sources.clear();

        for (auto u: temp) {
            for (auto v: shrinkAdj[u]) {
                inDegree[v] -= 1;
                if (inDegree[v] == 0)
                    sources.push_back(v);
            }
        }
    }

    if (valid)
        cout << "YA\n";
    else
        cout << "TIDAK\n";
}
