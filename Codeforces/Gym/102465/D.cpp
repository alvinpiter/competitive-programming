#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

//minY[x] -> minimum y at column x
int X, Y, N, minY[MAXN + 3], maxY[MAXN + 3], cntMinY[MAXN + 3], cntMaxY[MAXN + 3];
LL costAbove[MAXN + 3], costBelow[MAXN + 3];

int main() {
    scanf("%d%d", &X, &Y);
    scanf("%d", &N);

    for (int i = 0; i <= MAXN; i++) {
        minY[i] = Y;
        maxY[i] = -1;
    }

    for (int i = 1; i <= N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        minY[x] = min(minY[x], y);
        maxY[x] = max(maxY[x], y);
    }

    memset(cntMinY, 0, sizeof(cntMinY));
    memset(cntMaxY, 0, sizeof(cntMaxY));
    for (int x = 0; x < X; x++) {
        if (minY[x] != -1) {
            cntMinY[minY[x]] += 1;
            cntMaxY[maxY[x]] += 1;
        }
    }

    int cnt = 0;
    for (int y = 0; y < Y; y++) {
        costAbove[y] = (y == 0 ? 0 : costAbove[y - 1]) + 2 * cnt;
        cnt += cntMinY[y];
    }

    cnt = 0;
    for (int y = Y - 1; y >= 0; y--) {
        costBelow[y] = (y == Y - 1 ? 0 : costBelow[y + 1]) + 2 * cnt;
        cnt += cntMaxY[y];
    }

    LL minCost = 1e18;
    for (int y = 0; y < Y; y++) {
        LL cost = costAbove[y] + costBelow[y] + (X - 1);
        minCost = min(minCost, cost);
    }

    printf("%lld\n", minCost);
}
