/*
Model the system as a graph, where each node (except the first and the last) is an interval between two consecutive
teleport endpoints.

Observation:
The graph will consist of exactly 1 line graph and some (maybe 0) cycles.
The line graph is the the intervals that we will pass through, while the cycles are the intervals we won't pass through.

Observation:
The answer to the problem is K - 1, where K is the number of nodes in the final line graph. So our goal is to maximize
this value.

Observation:
Adding a teleport means that we will interfere at most 2 intervals, i.e nodes. There are 3 possible actions:
1. Add a teleport on an interval. This action adds 1 node to the affected subgraph, and also add 1 cycle with length 1.
2. Add a teleport that connects two different intervals:
   a. The intervals are in the same subgraph -> This is not beneficial.
   b. The intervals are in different subgraphs -> These subgraphs are merged into a larger subgraph, it has 2 more nodes.
   Picture the teleport "hooks" both subgraph.

Algorithm:
* Build the graph
* Identify the line graph and the cycles
* Connect the line graph to the longest cycles first, using action 2b above. Do this as many times as possible.
* If there is still teleports left to be built, alternate action 1 and 2b.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 2000000002
#define MAXN 1000000

int n, m, nxt[2 * MAXN + 3];
bool visited[2 * MAXN + 3];
vector<pair<int, int> > points;
vector<int> cycleLengths;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int w, e;
    cin >> w >> e;

    points.push_back({w, e});
    points.push_back({e, w});
  }

  memset(nxt, -1, sizeof(nxt));

  sort(points.begin(), points.end());

  for (int i = 0; i < points.size(); i++) {
    auto [x, otherEnd] = points[i];
    int idx = upper_bound(points.begin(), points.end(), make_pair(otherEnd, INF)) - points.begin();

    nxt[i] = idx;
  }

  memset(visited, false, sizeof(visited));

  // Process the line graph
  int numNodesInLineGraph = 0;
  int currentNode = 0;
  while (currentNode != -1) {
    numNodesInLineGraph += 1;
    visited[currentNode] = true;

    currentNode = nxt[currentNode];
  }

  // Process the cycles
  for (int i = 0; i < 2 * n + 1; i++) {
    if (!visited[i]) {
      int currentNode = i;
      int cycleLength = 0;
      while (!visited[currentNode]) {
        cycleLength += 1;
        visited[currentNode] = true;

        currentNode = nxt[currentNode];
      }

      cycleLengths.push_back(cycleLength);
    }
  }

  sort(cycleLengths.begin(), cycleLengths.end(), greater<int>());

  // Connect the line graph with the cycles while possible
  for (int i = 0; i < cycleLengths.size() && m > 0; i++, m--) {
    numNodesInLineGraph += cycleLengths[i] + 2;
  }

  // If we can add more teleports..
  numNodesInLineGraph += (m/2) * 4 + (m%2);

  cout << numNodesInLineGraph - 1 << endl;
}
