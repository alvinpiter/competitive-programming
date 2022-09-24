/*
We can find each rectangle with exactly k roses by using bruteforce + binary search, which will take O(N^3 log N) time.

We need to precalculate the following:
* bestWithLeft[i] = The minimal perimeter of rectangles with exactly k roses whose left end is at least i.
* bestWithRight[i], bestWithBottom[i], bestWithTop[i] are defined similarly.

For each rectangle with k roses, we then can find the second rectangle with k roses using the above 4 values.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXSIZE 250

int l, w, n, k, psum[MAXSIZE + 3][MAXSIZE + 3];
int bestWithLeft[MAXSIZE + 3], bestWithRight[MAXSIZE + 3], bestWithBottom[MAXSIZE + 3], bestWithTop[MAXSIZE + 3];

int query(int x1, int y1, int x2, int y2) {
  return psum[x2][y2] - psum[x1 - 1][y2] - psum[x2][y1 - 1] + psum[x1 - 1][y1 - 1];
}

/*
Return x1 such that the number of flowers in a rectangle with
lower-left corner (x, y) and top-right corner (x1, y1) is exactly k.

Returns -1 if there is none.
*/
int findX1(int x, int y, int y1) {
  int lo = x, hi = l, mid;
  while (hi >= lo) {
    mid = (lo + hi)/2;
    int sum = query(x, y, mid, y1);
    if (sum < k) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  if (query(x, y, lo, y1) == k) {
    return lo;
  } else {
    return -1;
  }
}

int main() {
  cin >> l >> w >> n >> k;

  memset(psum, 0, sizeof(psum));
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;

    psum[x][y] += 1;
  }

  for (int x = 1; x <= l; x++) {
    for (int y = 1; y <= w; y++) {
      psum[x][y] += psum[x - 1][y];
      psum[x][y] += psum[x][y - 1];
      psum[x][y] -= psum[x - 1][y - 1];
    }
  }

  for (int i = 0; i <= max(l, w) + 1; i++) {
    bestWithLeft[i] = bestWithRight[i] = bestWithBottom[i] = bestWithTop[i] = INF;
  }

  for (int x = 1; x <= l; x++) {
    for (int y = 1; y <= w; y++) {
      for (int y1 = y; y1 <= w; y1++) {
        int x1 = findX1(x, y, y1);
        if (x1 != -1) {
          int perimeter = 2*(x1 - x + 1) + 2*(y1 - y + 1);
          bestWithLeft[x] = min(bestWithLeft[x], perimeter);
          bestWithRight[x1] = min(bestWithRight[x1], perimeter);
          bestWithBottom[y] = min(bestWithBottom[y], perimeter);
          bestWithTop[y1] = min(bestWithTop[y1], perimeter);
        }
      }
    }
  }

  for (int x = l; x >= 1; x--) bestWithLeft[x] = min(bestWithLeft[x], bestWithLeft[x + 1]);
  for (int x = 1; x <= l; x++) bestWithRight[x] = min(bestWithRight[x], bestWithRight[x - 1]);
  for (int y = w; y >= 1; y--) bestWithBottom[y] = min(bestWithBottom[y], bestWithBottom[y + 1]);
  for (int y = 1; y <= w; y++) bestWithTop[y] = min(bestWithTop[y], bestWithTop[y - 1]);

  int ans = INF;
  for (int x = 1; x <= l; x++) {
    for (int y = 1; y <= w; y++) {
      for (int y1 = y; y1 <= w; y1++) {
        int x1 = findX1(x, y, y1);
        if (x1 != -1) {
          int perimeter = 2*(x1 - x + 1) + 2*(y1 - y + 1);
          ans = min(ans, perimeter + bestWithLeft[x1 + 1]);
          ans = min(ans, perimeter + bestWithRight[x - 1]);
          ans = min(ans, perimeter + bestWithBottom[y1 + 1]);
          ans = min(ans, perimeter + bestWithTop[y - 1]);
        }
      }
    }
  }

  if (ans < INF) {
    cout << ans << endl;
  } else {
    cout << "NO\n";
  }
}
