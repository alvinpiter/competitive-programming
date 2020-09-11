#include<bits/stdc++.h>
using namespace std;
#define MAXM 200000
#define MAXK 200000
#define MAXA 200000

struct Trap {
    int l, r, d;
    Trap() {}
    Trap(int _l, int _r, int _d): l(_l), r(_r), d(_d) {}
};

int M, N, K, T, A[MAXM + 3];
Trap traps[MAXK + 3];

int main() {
    scanf("%d%d%d%d", &M, &N, &K, &T);
    for (int i = 0; i < M; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < K; i++) {
        int l, r, d;
        scanf("%d%d%d", &l, &r, &d);

        traps[i] = Trap(l, r, d);
    }

    int lo, mid, hi;

    lo = 1;
    hi = MAXA;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        int prefixSum[MAXA + 3];
        memset(prefixSum, 0, sizeof(prefixSum));

        for (int i = 0; i < K; i++) {
            if (mid < traps[i].d) {
                prefixSum[traps[i].l] += 1;
                prefixSum[traps[i].r + 1] -= 1;
            }
        }

        for (int i = 1; i <= MAXA; i++)
            prefixSum[i] += prefixSum[i - 1];

        int totalTrap = 0;
        for (int i = 1; i <= MAXA; i++) {
            if (prefixSum[i] > 0) totalTrap += 1;
        }

        int totalTime = N + 1 + 2 * totalTrap;

        if (totalTime <= T)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    //Count how many soldiers with agility at least lo
    int answer = 0;
    for (int i = 0; i < M; i++) {
        if (A[i] >= lo)
            answer += 1;
    }

    printf("%d\n", answer);
}
