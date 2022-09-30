/*
A2 = D1 + A1
A3 = (D1 + D2) + A1
A4 = (D1 + D2 + D3) + A1

Brute force A1, and then make sure A2..A4 is within 1 to N (inclusive). The range check
can be simplified by only taking the minimum and the maximum among D1, D1 + D2, D1 + D2 + D3, etc.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1000000000000000
#define MAXN 300000

int main() {
  int N, D[MAXN + 3];

  scanf("%d", &N);

  LL sumD = 0;
  LL minSumD = INF, maxSumD = -INF;
  for (int i = 1; i < N; i++) {
    scanf("%d", &D[i]);

    sumD += D[i];
    minSumD = min(minSumD, sumD);
    maxSumD = max(maxSumD, sumD);
  }

  vector<int> possibleA1;
  for (int a1 = 1; a1 <= N; a1++) {
    if (minSumD + a1 < 1 || minSumD + a1 > N || maxSumD + a1 < 1 || maxSumD + a1 > N) {
      continue;
    } else {
      possibleA1.push_back(a1);
    }
  }

  if (possibleA1.size() > 1) {
    printf("-1\n");
  } else {
    printf("%d", possibleA1[0]);

    int prev = possibleA1[0];
    for (int i = 2; i <= N; i++) {
      printf(" %d", D[i - 1] + prev);
      prev = D[i - 1] + prev;
    }
    printf("\n");
  }
}
