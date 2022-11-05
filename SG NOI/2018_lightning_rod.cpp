/*
Assume we are currently at the i-th building.

A lightning rod located at a building to the left of the i-th building can cover the i-th building if:
Y[left] - Y[i] >= X[i] - X[left]
X[left] + Y[left] >= X[i] + Y[i]

A lightning rod located at a building to the right of the i-th building can cover the i-th building if:
Y[right] - Y[i] >= X[right] - X[i]
Y[right] - X[right] >= Y[i] - X[i]

If a lightning rod at the j-th building can cover the k-th building and a lightning rod at the i-th building can cover
the j-th building, then the lightning rod at the i-th building can also cover the k-th building. With this observation,
we can define a building as "dominant" as a building that can't be covered by any lightning rod located at another building.
The answer to the problem is then the number of "dominant" building.

To find out whether a building is "dominant" or not, we can do so by finding the "best" building to the left of
it and to the right of it. The best building to the left of it is the one with highest X[left] + Y[left], while the
best building to the right of it is the one with highest Y[right] - X[right].

The total complexity is O(N).
*/

#include <bits/stdc++.h>
using namespace std;
#define INF 2000000001
#define MAXN 10000000

inline int readInt() {
  int x = 0;
  char ch = getchar_unlocked();
  while (ch < '0' || ch > '9') ch = getchar_unlocked();
  while (ch >= '0' && ch <= '9'){
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar_unlocked();
  }
  return x;
}

int X[MAXN + 3], Y[MAXN + 3];
bool isDominant[MAXN + 3];

int main(){
	int N = readInt();
	for(int i = 0; i < N; i++) {
		X[i] = readInt();
		Y[i] = readInt();
    isDominant[i] = true;
	}

  int maxXPlusY = -INF;
  for (int i = 0; i < N; i++) {
    if (X[i] + Y[i] <= maxXPlusY) {
      isDominant[i] = false;
    }

    maxXPlusY = max(maxXPlusY, X[i] + Y[i]);
  }

  int maxYMinX = -INF;
  for (int i = N - 1; i >= 0; i--) {
    if (Y[i] - X[i] <= maxYMinX) {
      isDominant[i] = false;
    }

    maxYMinX = max(maxYMinX, Y[i] - X[i]);
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (isDominant[i]) {
      ans += 1;
    }
  }

  cout << ans << endl;
}
