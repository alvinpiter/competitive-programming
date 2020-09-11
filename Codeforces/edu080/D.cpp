#include<bits/stdc++.h>
using namespace std;
#define MAXN 300000
#define MAXM 8

int N, M, a[MAXN + 3][MAXM + 3];

//Returns a pair of indices whose minimax equals to 'minimax'
pair<int, int> getIndices(int minimax) {
    int who[(1 << MAXM) + 3]; //who[mask] = which array whose binary representation equals to mask

    memset(who, -1, sizeof(who));

    for (int i = 0; i < N; i++) {
        int mask = 0;
        for (int j = 0; j < M; j++) {
            if (a[i][j] >= minimax)
                mask |= (1 << j);
        }

        who[mask] = i;
    }

    for (int i = 0; i < (1 << M); i++) {
        for (int j = i; j < (1 << M); j++) {
            if ((i | j) == ((1 << M) - 1) && who[i] != -1 && who[j] != -1)
                return {who[i], who[j]};
        }
    }

    return {-1, -1};
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            scanf("%d", &a[i][j]);
    }

    int lo, mid, hi;
    lo = 0; hi = 1e9;

    while (hi >= lo) {
        mid = (lo + hi)/2;

        auto indices = getIndices(mid);
        if (indices.first == -1)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    auto indices = getIndices(hi);

    printf("%d %d\n", indices.first + 1, indices.second + 1);
}
