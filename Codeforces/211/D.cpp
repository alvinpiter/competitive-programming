#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
Sort the budget and the rent prices in non-decreasing order.

Observations:
* If we can rent x bikes, we can rent x - 1 bikes. This is a hint for binary search solution.
* Always rent the cheapest bikes first.
* If boy i..j each can rent a bike, then boy i+1..j+1 each can rent a bike (because they are richer). This means that we always let the richest boys rent first.
* When pairing the richest boys with the cheapest bikes, we can do it greedily, i.e pair the poorest (among the richest) to rent cheapest bike. This can be proofed using exchange argument (try to minimize the amount of used shared budget).
*/

int n, m, a, b[MAXN + 3], p[MAXN + 3];

/*
check if we can ren the first cnt cheapest bike
If it's possible to rent first cnt cheapest bike, return the minimum personal budget needed. Otherwise return -1
*/
int check(int cnt) {
    int sharedBudget = a;
    int totalPersonalBudget = 0;

    for (int i = 1; i <= cnt; i++) {
        int idxBudget = n - cnt + i;

        if (b[idxBudget] >= p[i]) {
            totalPersonalBudget += p[i];
        } else {
            int diff = p[i] - b[idxBudget];
            if (diff <= sharedBudget) {
                sharedBudget -= diff;
                totalPersonalBudget += b[idxBudget];
            } else {
                return -1;
            }
        }
    }

    totalPersonalBudget -= sharedBudget;
    totalPersonalBudget = max(totalPersonalBudget, 0);

    return totalPersonalBudget;
}

int main() {
    scanf("%d%d%d", &n, &m, &a);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);

    for (int i = 1; i <= m; i++)
        scanf("%d", &p[i]);

    sort(b + 1, b + n + 1);
    sort(p + 1, p + m + 1);

    int lo = 1, hi = min(n, m), mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        if (check(mid) < 0)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    if (hi == 0)
        printf("0 0\n");
    else
        printf("%d %d\n", hi, check(hi));
}
