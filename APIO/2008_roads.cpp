/*
Greedy solution:
* Process cobblestone roads whose endpoints are not connected via only concrete roads
* Process cobblestone roads other than the above
* Process concrete roads
* Check if the final network is connected
*/
#include<bits/stdc++.h>
using namespace std;

class UnionFind {
private:
  int N;
  vector<int> parent;
public:
  UnionFind(int n) {
    N = n;
    for (int i = 0; i <= N; i++) parent.push_back(i);
  }

  int findParent(int u) {
    return (parent[u] == u ? u : parent[u] = findParent(parent[u]));
  }

  bool isSameSet(int u, int v) {
    return findParent(u) == findParent(v);
  }

  void joinSet(int u, int v) {
    parent[findParent(u)] = findParent(v);
  }
};

int main() {
  int N, M, K;
  vector<pair<int, pair<int, int> > > edges, chosenEdges; // {type, {u, v}}

  cin >> N >> M >> K;

  UnionFind concreteNetwork(N);
  UnionFind finalNetwork(N);

  for (int i = 1; i <= M; i++) {
    int u, v, type;
    cin >> u >> v >> type;

    edges.push_back({type, {u, v}});
    if (type == 1) {
      concreteNetwork.joinSet(u, v);
    }
  }

  // Process cobblestone roads whose ends are disconnected in concrete network
  for (auto [type, endpoints]: edges) {
    auto [u, v] = endpoints;
    if (type == 0 && !concreteNetwork.isSameSet(u, v)) {
      if (chosenEdges.size() < K && !finalNetwork.isSameSet(u, v)) {
        finalNetwork.joinSet(u, v);
        chosenEdges.push_back({type, endpoints});
      }
    }
  }

  // Process cobblestone roads whose ends are connected in concrete network
  for (auto [type, endpoints]: edges) {
    auto [u, v] = endpoints;
    if (type == 0 && concreteNetwork.isSameSet(u, v)) {
      if (chosenEdges.size() < K && !finalNetwork.isSameSet(u, v)) {
        finalNetwork.joinSet(u, v);
        chosenEdges.push_back({type, endpoints});
      }
    }
  }

  if (chosenEdges.size() < K) {
    cout << "no solution\n";
    return 0;
  }

  // Process concrete roads
  for (auto [type, endpoints]: edges) {
    auto [u, v] = endpoints;
    if (type == 1 && !finalNetwork.isSameSet(u, v)) {
      finalNetwork.joinSet(u, v);
      chosenEdges.push_back({type, endpoints});
    }
  }

  // Make sure the final network is connected
  bool isConnected = true;
  for (int i = 2; i <= N; i++) {
    if (!finalNetwork.isSameSet(1, i)) {
      isConnected = false;
    }
  }

  if (!isConnected) {
    cout << "no solution\n";
    return 0;
  }

  for (auto edge: chosenEdges) {
    cout << edge.second.first << " " << edge.second.second << " " << edge.first << endl;
  }
}
