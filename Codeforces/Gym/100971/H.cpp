#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
How to solve this problem for some k:
* Create a binary array with size n, let's say its name is array s.
* s[i] = 1 if a[i] <= k <= b[i], 0 otherwise.

The answer is the first index such that the prefix sum is k.

Now, if we move k to k + 1, we need to:
* Change the indices i where b[i] = k
* Change the indices i where a[i] = k + 1

To speed up the process, use BIT
*/

int n;
int bit[MAXN + 3];
vector<int> startsAt[MAXN + 3], endsAt[MAXN + 3]; //contains indices.

void update(int idx, int val) {
    while (idx <= n) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        startsAt[a].push_back(i);
        endsAt[b].push_back(i);
    }

    memset(bit, 0, sizeof(bit));
    for (int k = 1; k <= n; k++) {
        for (auto idx: endsAt[k - 1])
            update(idx, -1);

        for (auto idx: startsAt[k])
            update(idx, 1);

        int lo = 1, hi = n, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (query(mid) < k)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        if (lo == n + 1)
            printf("-1");
        else
            printf("%d", lo);

        if (k == n)
            printf("\n");
        else
            printf(" ");
    }
}
