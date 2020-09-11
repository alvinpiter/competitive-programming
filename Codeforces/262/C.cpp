#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int main() {
    int n, m, w, a[MAXN + 3], undo[MAXN + 3];

    scanf("%d%d%d", &n, &m, &w);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    int lo = 1, hi = 1e9 + m, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        memset(undo, 0, sizeof(undo));
        int cnt = 0;
        int sum = 0;

        for (int i = 1; i <= n && cnt <= m; i++) {
            sum += undo[i];

            int height = sum + a[i];
            int add = max(0, mid - height);

            cnt += add;
            sum += add;
            if (i + w <= n)
                undo[i + w] -= add;
        }

        if (cnt > m)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    printf("%d\n", hi);
}
