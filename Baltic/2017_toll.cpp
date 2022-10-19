/*
Picture the nodes are arranged in a 2D matrix with K rows
where each column contains nodes with the same floor(index/K).

dp[node][jump][k] = minimum cost to go from node "node" to the k-th node located in column node/K + 2^jump.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 50000
#define MAXLG 15
#define MAXK 5

int K, N, M, Q, dp[MAXN + 3][MAXLG + 3][MAXK + 3];

int main() {
  cin >> K >> N >> M >> Q;

  for (int i = 0; i < N; i++) {
    for (int jump = 0; jump <= MAXLG; jump++) {
      for (int k = 0; k <= K; k++) {
        dp[i][jump][k] = INF;
      }
    }
  }

  for (int i = 0; i < M; i++) {
    int a, b, t;
    cin >> a >> b >> t;

    dp[a][0][b%K] = t;
  }

  int numberOfColumns = N/K + (N%K == 0 ? 0 : 1);
  for (int jump = 1; jump <= MAXLG; jump++) {
    for (int i = 0; i < N; i++) {
      int currentColumn = i/K;
      int destinationColumn = currentColumn + (1 << jump);

      if (destinationColumn >= numberOfColumns) {
        continue;
      }

      for (int destinationK = 0; destinationK < K; destinationK++) {
        for (int transitK = 0; transitK < K; transitK++) {
          int transitColumn = currentColumn + (1 << (jump - 1));
          int transitNode = transitColumn * K + transitK;

          dp[i][jump][destinationK] = min(dp[i][jump][destinationK], dp[i][jump - 1][transitK] + dp[transitNode][jump - 1][destinationK]);
        }
      }
    }
  }

  for (int q = 0; q < Q; q++) {
    int a, b;
    cin >> a >> b;

    int currentColumn = a/K, destinationColumn = b/K;
    int columnDiff = destinationColumn - currentColumn;

    map<int, int> currentNodes;
    currentNodes[a] = 0;

    for (int jump = 0; jump <= MAXLG; jump++) {
      if (columnDiff & (1 << jump)) {
        map<int, int> newNodes;

        for (auto [currentNode, currentCost]: currentNodes) {
          for (int destinationK = 0; destinationK < K; destinationK++) {
            int destinationColumn = currentColumn + (1 << jump);
            int destinationNode = destinationColumn * K + destinationK;
            int newCost = min(INF, currentCost + dp[currentNode][jump][destinationK]);

            if (newNodes.find(destinationNode) == newNodes.end()) {
              newNodes[destinationNode] = newCost;
            } else {
              newNodes[destinationNode] = min(newNodes[destinationNode], newCost);
            }
          }
        }

        swap(currentNodes, newNodes);
        currentColumn += (1 << jump);
      }
    }

    if (currentNodes.find(b) != currentNodes.end() && currentNodes[b] < INF) {
      cout << currentNodes[b] << endl;
    } else {
      cout << -1 << endl;
    }
  }
}
