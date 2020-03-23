
/*
4
1 1 2 2 2 2 5 5
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int n, a[MAXN + 3];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++)
        scanf("%d", &a[i]);

    sort(a, a + 2 * n);

    LL answer = 1e18;
    for (int i = 0; i <= n; i++) {
        LL area;
        if (i == 0)
            area = (LL) (a[n - 1] - a[0]) * (a[2*n - 1] - a[n]);
        else
            area = (LL) (a[i + n - 1] - a[i]) * (a[2*n - 1] - a[0]);

        answer = min(answer, area);
    }

    printf("%lld\n", answer);
}
