#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000
#define LL long long int

int N, M, P;
LL A[MAXN + 3][MAXN + 3], prefixSum[MAXN + 3][MAXN + 3];

LL query(int r1, int c1, int r2, int c2) {
    r1 = max(r1, 1);
    c1 = max(c1, 1);
    return prefixSum[r2][c2] - prefixSum[r1 - 1][c2] - prefixSum[r2][c1 - 1] + prefixSum[r1 - 1][c1 - 1];
}

int main() {
    scanf("%d%d%d", &N, &M, &P);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++)
            scanf("%lld", &A[i][j]);
    }

    memset(prefixSum, 0, sizeof(prefixSum));

    bool valid = true;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];

            LL currentSum = query(i - P + 1, j - P + 1, i, j);

            if (currentSum > A[i][j]) {
                valid = false;
                break;
            }

            LL diff = A[i][j] - currentSum;

            if (i + P - 1 <= N && j + P - 1 <= M)
                prefixSum[i][j] += diff;
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (query(i - P + 1, j - P + 1, i, j) != A[i][j])
                valid = false;
        }
    }

    if (valid)
        printf("YA\n");
    else
        printf("TIDAK\n");
}
