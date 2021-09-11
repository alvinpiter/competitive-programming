#include "shoes.h"
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int tree[4 * 2 * MAXN + 3], lazy[4 * 2 * MAXN + 3];

int evaluate(int node, int l, int r) {
  return tree[node] + (r - l + 1) * lazy[node];
}

void pushDown(int node, int l, int r) {
  if (l == r) {
    return;
  }

  lazy[2 * node] += lazy[node];
  lazy[2 * node + 1] += lazy[node];
  lazy[node] = 0;
}

void pullUp(int node, int l, int r) {
  int m = (l + r)/2;
  tree[node] = evaluate(2 * node, l, m) + evaluate(2 * node + 1, m + 1, r);
}

void update(int node, int l, int r, int left, int right, int val) {
  if (r < left || l > right) {
    return;
  }

  if (l >= left && r <= right) {
    lazy[node] += val;
    return;
  }

  pushDown(node, l, r);

  int m = (l + r)/2;
  update(2 * node, l, m, left, right, val);
  update(2 * node + 1, m + 1, r, left, right, val);

  pullUp(node, l, r);
}

int query(int node, int l, int r, int idx) {
  if (l == r) {
    return evaluate(node, l, r);
  }

  pushDown(node, l, r);

  int m = (l + r)/2;
  int result;
  if (idx <= m) {
    result = query(2 * node, l, m, idx);
  } else {
    result = query(2 * node + 1, m + 1, r, idx);
  }

  pullUp(node, l, r);
  return result;
}

long long count_swaps(std::vector<int> s) {
  int N = s.size();

  memset(tree, 0, sizeof(tree));
  memset(lazy, 0, sizeof(lazy));

  bool done[2 * MAXN + 3];
  memset(done, false, sizeof(done));

  vector<int> pos[2 * MAXN + 3];
  for (int i = N; i >= 1; i--) {
    pos[s[i - 1] + MAXN].push_back(i); //Make it 1-based
  }

  long long int answer = 0;
  for (int i = 1; i <= N; i++) {
    if (done[i]) {
      continue;
    }

    int firstOriginalIndex = pos[s[i - 1] + MAXN].back();
    pos[s[i - 1] + MAXN].pop_back();
    done[firstOriginalIndex] = true;

    int secondOriginalIndex = pos[-s[i - 1] + MAXN].back();
    pos[-s[i - 1] + MAXN].pop_back();
    done[secondOriginalIndex] = true;

    int firstNewIndex = firstOriginalIndex + query(1, 1, N, firstOriginalIndex);
    int secondNewIndex = secondOriginalIndex + query(1, 1, N, secondOriginalIndex);

    if (s[i - 1] < 0) {
      //current shoe is left shoe
      answer += (secondNewIndex - firstNewIndex - 1);
    } else {
      //current shoe is right shoe
      answer += (secondNewIndex - firstNewIndex);
    }

    if (firstOriginalIndex + 1 < secondOriginalIndex) {
      update(1, 1, N, firstOriginalIndex + 1, secondOriginalIndex - 1, 1);
    }
  }

  return answer;
}

// int main() {
//   int n;
//   vector<int> v;

//   cin >> n;
//   for (int i = 1; i <= n; i++) {
//     int num;
//     cin >> num;

//     v.push_back(num);
//   }

//   cout << count_swaps(v) << endl;
// }

/*
3
-3 -2 2 1 3 -1
*/
