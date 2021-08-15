#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int N, Q, H[MAXN + 3], answer[MAXN + 3], tree[4 * MAXN + 3];
LL prefixSum[MAXN + 3];
vector<pair<LL, int> > queries;

int lastProcessedQuery = -1;

void buildSegmentTree(int node, int left, int right) {
  if (left == right) {
    tree[node] = left;
    return;
  }

  int mid = (left + right)/2;
  buildSegmentTree(2 * node, left, mid);
  buildSegmentTree(2 * node + 1, mid + 1, right);

  tree[node] = H[tree[2 * node]] <= H[tree[2 * node + 1]] ? tree[2 * node] : tree[2 * node + 1];
}

int queryIndexWithMinimalHeight(int node, int left, int right, int qLeft, int qRight) {
  if (left >= qLeft && right <= qRight) {
    return tree[node];
  }

  if (qRight < left || qLeft > right) {
    return -1;
  }

  int mid = (left + right)/2;

  int leftResult = queryIndexWithMinimalHeight(2 * node, left, mid, qLeft, qRight);
  int rightResult = queryIndexWithMinimalHeight(2 * node + 1, mid + 1, right, qLeft, qRight);

  if (leftResult == -1) {
    return rightResult;
  } else if (rightResult == -1) {
    return leftResult;
  } else {
    if (H[leftResult] <= H[rightResult]) {
      return leftResult;
    } else {
      return rightResult;
    }
  }
}

/*
heightOffset -> height of the minimum stacks before we get to this state
costOffset -> number of blocks that has been taken before we get to this state
*/
void solve(int left, int right, int heightOffset, LL costOffset) {
  int indexWithMinimalHeight = queryIndexWithMinimalHeight(1, 1, N, left, right);
  int minimalHeight = H[indexWithMinimalHeight] - heightOffset;
  int numberOfStacks = right - left + 1;

  /*
  Maximal number of blocks that can be taken before
  this segment is broken down into more segments.
  */
  LL currentCost = (LL) minimalHeight * numberOfStacks;

  for (int i = lastProcessedQuery + 1; i < queries.size(); i++) {
    LL q = queries[i].first;
    int index = queries[i].second;

    if (q - costOffset <= currentCost) {
      answer[index] = (q - costOffset)%numberOfStacks == 0 ? right : (left - 1) + (q - costOffset)%numberOfStacks;
      lastProcessedQuery = i;
    } else {
      break;
    }
  }

  if (indexWithMinimalHeight > left) {
    solve(left, indexWithMinimalHeight - 1, H[indexWithMinimalHeight], costOffset + currentCost);
  }

  if (indexWithMinimalHeight < right) {
    LL costLeft = indexWithMinimalHeight == left ?
      0 :
      (prefixSum[indexWithMinimalHeight - 1] - prefixSum[left - 1]) - (LL) H[indexWithMinimalHeight] * (indexWithMinimalHeight - left);

    solve(indexWithMinimalHeight + 1, right, H[indexWithMinimalHeight], costOffset + currentCost + costLeft);
  }
}

int main() {
  scanf("%d", &N);

  prefixSum[0] = 0;
  for (int i = 1; i <= N; i++) {
    scanf("%d", &H[i]);
    prefixSum[i] = prefixSum[i - 1] + H[i];
  }

  scanf("%d", &Q);
  for (int i = 1; i <= Q; i++) {
    LL k;
    scanf("%lld", &k);

    queries.push_back(make_pair(k, i));
  }

  buildSegmentTree(1, 1, N);
  sort(queries.begin(), queries.end()); //Process queries starting from the smallest one.

  solve(1, N, 0, 0);

  for (int i = 1; i <= Q; i++) {
    printf("%d\n", answer[i]);
  }
}
