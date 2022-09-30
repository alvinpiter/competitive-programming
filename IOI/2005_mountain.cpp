/*
Need to create a data structure that support the following queries:
* update(l, r, v) -> Set the values in range l..r to v.
* query(h) -> Get the largest index i such that sum(j) <= h, for all j <= i. sum(j) is the sum of the first j numbers.

We can maintain a segment tree where each node has the following information:
* sum -> the sum of elements this node is responsible for
* maxSum -> the max cumulative sum of elements this node is responsible for

When merging two nodes, we do the following:
sum = sumLeft + sumRight
maxSum = max(maxSumLeft, sumLeft + maxSumRight)

Need to implement struct-based segment tree so we don't have to perform coordinate compression.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000001
#define MAXN 200000

struct Node {
  int l, r, sum, maxSum, lazy;
  Node *leftChild, *rightChild;
  Node(int l_, int r_): l(l_), r(r_), sum(0), maxSum(0), lazy(-INF) {}
  void generateChildren() {
    if (leftChild == NULL) {
      int m = (l + r)/2;
      leftChild = new Node(l, m);
      rightChild = new Node(m + 1, r);
    }
  }

  int evaluateSum() {
    return lazy == -INF ? sum : (r - l + 1) * lazy;
  }

  int evaluateMaxSum() {
    return lazy == -INF ? maxSum : max(lazy, (r - l + 1) * lazy);
  }

  void pushDown() {
    if (lazy != -INF && leftChild != NULL && rightChild != NULL) {
      leftChild->lazy = lazy;
      rightChild->lazy = lazy;
      lazy = -INF;
    }
  }

  void pullUp() {
    if (leftChild != NULL && rightChild != NULL) {
      sum = leftChild->evaluateSum() + rightChild->evaluateSum();
      maxSum = max(leftChild->evaluateMaxSum(), leftChild->evaluateSum() + rightChild->evaluateMaxSum());
    }
  }

  bool isLeaf() {
    return leftChild == NULL && rightChild == NULL;
  }
};

void update(Node *current, int l, int r, int val) {
  if (current->l > r || current->r < l) {
    return;
  }

  if (current->l >= l && current->r <= r) {
    current->lazy = val;
    return;
  }

  current->generateChildren();
  current->pushDown();

  update(current->leftChild, l, r, val);
  update(current->rightChild, l, r, val);

  current->pullUp();
}

int query(Node *current, int h) {
  if (current->l == current->r) {
    if (current->evaluateMaxSum() <= h) {
      return current->r;
    } else {
      return current->l - 1;
    }
  }

  current->generateChildren();
  current->pushDown();

  int result;
  if (current->leftChild->evaluateMaxSum() <= h) {
    result = query(current->rightChild, h - current->leftChild->evaluateSum());
  } else {
    result = query(current->leftChild, h);
  }

  current->pullUp();

  return result;
}

int main() {
  int N, a, b, d, h;
  string command;

  cin >> N;
  Node *root = new Node(1, N);
  while (true) {
    cin >> command;
    if (command == "E") {
      break;
    } else if (command == "I") {
      cin >> a >> b >> d;
      update(root, a, b, d);
    } else if (command == "Q") {
      cin >> h;
      cout << query(root, h) << endl;
    }
  }
}
