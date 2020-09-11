#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int t, n, k, a[MAXN + 3], peakSum[MAXN + 3];

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d", &n, &k);

        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            peakSum[i] = 0;
        }

        for (int i = 2; i < n; i++) {
            if (a[i] > a[i - 1] && a[i] > a[i + 1])
                peakSum[i] += 1;
        }

        for (int i = 2; i <= n; i++)
            peakSum[i] += peakSum[i - 1];

        int ans1 = 0;
        int ans2 = 1;
        for (int i = 1; i + k - 1 <= n; i++) {
            int cnt = peakSum[i + k - 2] - peakSum[i];
            if (cnt + 1 > ans1) {
                ans1 = cnt + 1;
                ans2 = i;
            }
        }

        printf("%d %d\n", ans1, ans2);
    }
}
