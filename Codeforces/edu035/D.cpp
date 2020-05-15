#include<bits/stdc++.h>
using namespace std;
#define MAXN 1500

/*
Imagine we reverse segment l..r. If initially there are i inversions in segment l..r, after inversion
there will be C(n, 2) - i inversions in segment l..r.

So after reversing, the global parity changes by -2*i + C(n, 2).
Notice that -2*i can't change the global parity, while C(n, 2) can.
So we need to only consider the parity of C(n, 2).
*/

int main() {
    int n, m, a[MAXN + 3], inversionParity;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    inversionParity = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] > a[j])
                inversionParity += 1;
        }
    }

    inversionParity %= 2;

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);

        int cnt = r - l + 1;
        int parityChange = ((cnt * cnt - cnt)/2)%2;

        inversionParity = (inversionParity + parityChange)%2;

        if (inversionParity == 0)
            printf("even\n");
        else
            printf("odd\n");
    }
}
