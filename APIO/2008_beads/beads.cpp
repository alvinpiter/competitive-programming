#include "beads.h"
#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 300000

/*
beadPath[i] -> The path taken by the i-th bead.
The data is stored as {swapper index, the position of the bead after going through this swapper}.
Each swapper appears in 2 beadPath, so the total number of data this vector holds is still O(N).
*/
vector<pair<int, int> > beadPath[MAXN + 3];

void init(int N, int M, std::vector<int> A) {
  /*
  swappers[i] -> swappers that affect the i-th conveyor belt.
  The data is stored as {swapper index, the conveyor belt index after going through it}.
  */
  vector<pair<int, int> > swappers[MAXN + 3];

  for (int swapperIndex = 1; swapperIndex <= M; swapperIndex++) {
    swappers[A[swapperIndex - 1]].push_back({swapperIndex, A[swapperIndex - 1] + 1});
    swappers[A[swapperIndex - 1] + 1].push_back({swapperIndex, A[swapperIndex - 1]});
  }

  for (int j = 1; j <= N; j++) {
    while (true) {
      int currentPos = (beadPath[j].empty() ? j : beadPath[j].back().second);
      int lastSwapperIndex = (beadPath[j].empty() ? 0 : beadPath[j].back().first);

      auto ptrToNextSwapper = upper_bound(swappers[currentPos].begin(), swappers[currentPos].end(), make_pair(lastSwapperIndex, INF));
      if (ptrToNextSwapper == swappers[currentPos].end()) {
        break;
      } else {
        beadPath[j].push_back(*ptrToNextSwapper);
      }
    }
  }
}

int ask(int K, int J) {
  int lo = 0, hi = beadPath[K].size() - 1, mid;
  while (hi >= lo) {
    mid = (lo + hi)/2;
    if (beadPath[K][mid].first <= J) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  return (hi == -1 ? K : beadPath[K][hi].second);
}
