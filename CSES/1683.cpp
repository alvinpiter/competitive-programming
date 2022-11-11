#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M;
vector<int> adj[MAXN + 3];

int currentDfsTime = 0, dfsTime[MAXN + 3], minDfsTime[MAXN + 3];
bool isActive[MAXN + 3];
vector<int> nodes;

int numberOfNodesInDAG = 0;
int nodeNumInDAG[MAXN + 3];

void dfs(int u) {
  dfsTime[u] = minDfsTime[u] = ++currentDfsTime;
  isActive[u] = true;
  nodes.push_back(u);

  for (auto v: adj[u]) {
    if (dfsTime[v] == -1) {
      dfs(v);
    }

    if (isActive[v]) {
      minDfsTime[u] = min(minDfsTime[u], minDfsTime[v]);
    }
  }

  if (dfsTime[u] == minDfsTime[u]) {
    ++numberOfNodesInDAG;
    while (true) {
      int node = nodes.back();

      nodes.pop_back();
      isActive[node] = false;

      nodeNumInDAG[node] = numberOfNodesInDAG;

      if (node == u) break;
    }
  }
}

int main() {
  cin >> N >> M;

  for (int i = 1; i <= M; i++) {
    int start, end;
    cin >> start >> end;

    adj[start].push_back(end);
  }

  memset(dfsTime, -1, sizeof(dfsTime));
  memset(isActive, false, sizeof(isActive));
  for (int i = 1; i <= N; i++) {
    if (dfsTime[i] == -1) {
      dfs(i);
    }
  }

  cout << numberOfNodesInDAG << endl;
  for (int i = 1; i <= N; i++) {
    if (i > 1) cout << " ";
    cout << nodeNumInDAG[i];
  }
  cout << endl;
}
