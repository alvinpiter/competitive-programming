#include<bits/stdc++.h>
using namespace std;
#define MAXV 400000

int q, x, y, counter[MAXV + 3], ans, column;

int main() {
    scanf("%d%d", &q, &x);

    memset(counter, 0, sizeof(counter));

    ans = 0;
    column = 1;
    for (int i = 1; i <= q; i++) {
        scanf("%d", &y);

        counter[y%x] += 1;

        while (counter[ans%x] >= column) {
            ans += 1;
            if (ans % x == 0)
                column += 1;
        }

        printf("%d\n", ans);
    }
}
