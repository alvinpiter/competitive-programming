#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, a[200003], k;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        sort(a + 1, a + n + 1);

        k = min(a[n - 1], a[n]) - 1;
        k = min(k, n - 2);

        printf("%d\n", k);
    }
}
