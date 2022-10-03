/*
Segment tree with lazy propagation.

At each node, maintain the following information:
mini -> Largest "at least val" operation.
maxi -> Smallest "at most val" operation.

When pushing down the value down the tree, update with the following formula:
miniChild = min(maxiParent, max(miniChild, miniParent));
maxiChild = max(miniParent, min(maxiChild, maxiParent));
*/

#include "wall.h"
#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 2000000

struct Node {
  int mini, maxi;
  Node(int mini_ = 0, int maxi_ = INF): mini(mini_), maxi(maxi_) {}
};

int N;
Node lazy[4 * MAXN + 3];

void pushDown(int nodeNum) {
  lazy[2 * nodeNum] = Node(
    min(lazy[nodeNum].maxi, max(lazy[2 * nodeNum].mini, lazy[nodeNum].mini)),
    max(lazy[nodeNum].mini, min(lazy[2 * nodeNum].maxi, lazy[nodeNum].maxi))
  );

  lazy[2 * nodeNum + 1] = Node(
    min(lazy[nodeNum].maxi, max(lazy[2 * nodeNum + 1].mini, lazy[nodeNum].mini)),
    max(lazy[nodeNum].mini, min(lazy[2 * nodeNum + 1].maxi, lazy[nodeNum].maxi))
  );

  lazy[nodeNum] = Node(0, INF);
}

void doUpdate(int nodeNum, int l, int r, int type, int ql, int qr, int val) {
  if (qr < l || ql > r) {
    return;
  }

  if (l >= ql && r <= qr) {
    if (type == 1) {
      // "at least val"
      lazy[nodeNum].mini = max(lazy[nodeNum].mini, val);
      lazy[nodeNum].maxi = max(lazy[nodeNum].maxi, val);
    } else if (type == 2) {
      // "at most val"
      lazy[nodeNum].mini = min(lazy[nodeNum].mini, val);
      lazy[nodeNum].maxi = min(lazy[nodeNum].maxi, val);
    }

    return;
  }

  pushDown(nodeNum);

  int m = (l + r)/2;
  doUpdate(2 * nodeNum, l, m, type, ql, qr, val);
  doUpdate(2 * nodeNum + 1, m + 1, r, type, ql, qr, val);
}

void update(int type, int ql, int qr, int val) {
  doUpdate(1, 1, N, type, ql, qr, val);
}

int doQuery(int nodeNum, int l, int r, int idx) {
  if (l == r) {
    return lazy[nodeNum].mini;
  }

  pushDown(nodeNum);

  int m = (l + r)/2;
  if (idx <= m) {
    return doQuery(2 * nodeNum, l, m, idx);
  } else {
    return doQuery(2 * nodeNum + 1, m + 1, r, idx);
  }
}

int query(int idx) {
  return doQuery(1, 1, N, idx);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
  N = n;

  // Initialize tree
  for (int i = 1; i <= 4 * N; i++) {
    lazy[i] = Node(0, INF);
  }

  for (int i = 0; i < k; i++) {
    update(op[i], left[i] + 1, right[i] + 1, height[i]);
  }

  for (int i = 0; i < n; i++) {
    finalHeight[i] = query(i + 1);
  }

  return;
}
