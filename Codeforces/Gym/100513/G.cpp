#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

/*
For each segment starting from the left most, if its sum is > 0, then we will decrease the right most elements first.
Maintain a deque to store indices that can be reduced.
*/

int n, k, mini;
int bit[MAXN + 3];

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

int rsq(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    scanf("%d%d", &n, &k);

    memset(bit, 0, sizeof(bit));
    mini = 1e9;

    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        update(i, a);
        mini = min(mini, a);
    }

    //reducible indices
    deque<int> indices;
    for (int i = 1; i < k; i++)
        indices.push_back(i);

    LL cost = 0;
    for (int i = 1; i + k - 1 <= n; i++) {
        indices.push_back(i + k - 1);
        while (indices.front() < i)
            indices.pop_front();

        int currentSum = rsq(i, i + k - 1);
        if (currentSum < 0)
            continue;

        int toDecrease = currentSum + 1;

        cost += toDecrease;

        while (toDecrease > 0) {
            int idx = indices.back();
            int value = rsq(idx, idx);

            if (value == mini) {
                indices.pop_back();
                continue;
            }

            int canTake = value - mini;
            int take = min(toDecrease, canTake);

            toDecrease -= take;
            update(idx, -take);
        }
    }

    printf("%lld\n", cost);
    for (int i = 1; i <= n; i++)
        printf("%d ", rsq(i, i));
    printf("\n");
}
