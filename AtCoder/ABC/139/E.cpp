#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000
#define MAXM 1000000

int N, M, A[MAXN + 3], idx[MAXN + 3][MAXN + 3];
int inDegree[MAXM + 3], visited[MAXM + 3];
vector<int> adj[MAXM + 3];

void generateIndex() {
    M = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            M += 1;
            idx[i][j] = idx[j][i] = M;
        }
    }
}

bool DFS(int u, int prv) {
    visited[u] = 1;

    bool cycleExist = false;
    for (auto v: adj[u]) {
        if (visited[v] == 1) {
            if (v != prv) cycleExist = true;
        } else if (visited[v] == -1) {
            cycleExist |= DFS(v, u);
        }
    }

    visited[u] = 2;

    return cycleExist;
}

bool checkCycle() {
    bool cycleExist = false;

    memset(visited, -1, sizeof(visited));
    for (int i = 1; i <= M; i++) {
        if (visited[i] == -1)
            cycleExist |= DFS(i, 1);
    }

    return cycleExist;
}

int main() {
    cin >> N;

    generateIndex();

    memset(inDegree, 0, sizeof(inDegree));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N - 1; j++) {
            cin >> A[j];
            if (j > 1) {
                int u = idx[i][A[j - 1]];
                int v = idx[i][A[j]];
                adj[u].push_back(v);
                inDegree[v] += 1;
            }
        }
    }

    if (checkCycle()) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> sources; //node with zero indegree
    for (int i = 1; i <= M; i++) {
        if (inDegree[i] == 0) sources.push_back(i);
    }

    int answer = 0;
    while (sources.size() > 0) {
        answer += 1;

        vector<int> tempSources;

        for (auto u: sources) {
            for (auto v: adj[u]) {
                inDegree[v] -= 1;
                if (inDegree[v] == 0) tempSources.push_back(v);
            }
        }

        sources.clear();
        for (auto u: tempSources) sources.push_back(u);
    }

    cout << answer << endl;
}
