#include<bits/stdc++.h>
using namespace std;

int main() {
    int q, n, x, y, f1, f2, f3, f4;
    int minX, minY, maxX, maxY;

    scanf("%d", &q);
    for (int cases = 1; cases <= q; cases++) {
        scanf("%d", &n);

        minX = minY = -100000;
        maxX = maxY = +100000;

        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d%d%d%d", &x, &y, &f1, &f2, &f3, &f4);

            if (f1 == 0)
                minX = max(minX, x);

            if (f2 == 0)
                maxY = min(maxY, y);

            if (f3 == 0)
                maxX = min(maxX, x);

            if (f4 == 0)
                minY = max(minY, y);
        }

        if (minX > maxX || minY > maxY)
            printf("0\n");
        else
            printf("1 %d %d\n", minX, minY);
    }
}
