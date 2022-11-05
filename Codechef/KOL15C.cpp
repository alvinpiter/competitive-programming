#include<bits/stdc++.h>
using namespace std;
#define THRESHOLD 320
#define MAXN 100000

int N, U, ans[MAXN + 3], cnt[MAXN + 3][THRESHOLD + 3];

int main() {
  scanf("%d%d", &N, &U);

  memset(ans, 0, sizeof(ans));
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= U; i++) {
    int a, b;
    scanf("%d%d", &a, &b);

    if (a <= THRESHOLD) {
      cnt[b][a] += 1;
    } else {
      for (int current = b; current <= N; current += a) {
        ans[current] += 1;
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= THRESHOLD; j++) {
      ans[i] += cnt[i][j];
      if (i + j <= N) {
        cnt[i + j][j] += cnt[i][j];
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    if (i > 1) printf(" ");
    printf("%d", ans[i]);
  }
  printf("\n");
}
