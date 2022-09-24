/*
Convert the tree into a binary tree by adding nodes with distance and number of trees equal to 0.

The problem can be solved with the following dynamic programming formula:

dp[node][last][left] = Minimum cost to deliver all trees in the subtree rooted at "node", where the last installed sawmill
is at node "last", and we can build "left" additional sawmills.

At each node, we can either build a sawmill or not. And then split the number of additional sawmills among the two children.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 2000000001
#define MAXN 200
#define MAXK 50

int n, k, w[MAXN + 3], d[MAXN + 3], dist[MAXN + 3], dp[MAXN + 3][MAXN + 3][MAXK + 3];
int leftChild[MAXN + 3], rightChild[MAXN + 3];
vector<int> children[MAXN + 3];

void binarize(int node) {
  if (children[node].size() == 0) {
    leftChild[node] = rightChild[node] = -1;
    return;
  } else {
    leftChild[node] = children[node][0];
    binarize(leftChild[node]);

    int prev = node;
    for (int i = 1; i < (int) children[node].size(); i++) {
      int curr = ++n;
      w[curr] = d[curr] = 0;

      rightChild[prev] = curr;
      leftChild[curr] = children[node][i];
      binarize(leftChild[curr]);

      prev = curr;
    }

    rightChild[prev] = ++n;
    binarize(rightChild[prev]);
  }
}

void dfsDistance(int node) {
  if (node == -1) {
    return;
  }

  dist[leftChild[node]] = dist[node] + d[leftChild[node]];
  dfsDistance(leftChild[node]);

  dist[rightChild[node]] = dist[node] + d[rightChild[node]];
  dfsDistance(rightChild[node]);
}

int solve(int node, int last, int left) {
  if (node == -1) {
    return 0;
  }

  if (dp[node][last][left] != -1) {
    return dp[node][last][left];
  }

  int noSawmill = INF;
  int buildSawmill = INF;
  for (int newLeft = 0; newLeft <= left; newLeft++) {
    noSawmill = min(noSawmill, (dist[node] - dist[last])*w[node] + solve(leftChild[node], last, newLeft) + solve(rightChild[node], last, left - newLeft));
    if (left > 0 && newLeft < left) {
      buildSawmill = min(buildSawmill, solve(leftChild[node], node, newLeft) + solve(rightChild[node], node, left - 1 - newLeft));
    }
  }

  return dp[node][last][left] = min(noSawmill, buildSawmill);
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> w[i] >> p >> d[i];
    children[p].push_back(i);
  }

  binarize(0);

  dist[0] = 0;
  dfsDistance(0);

  memset(dp, -1, sizeof(dp));
  cout << solve(0, 0, k) << endl;
}
