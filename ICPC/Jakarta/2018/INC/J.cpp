#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int N, M, A[MAXN + 3];
LL mini, maxi;

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    sort(A, A + N);

    mini = 0;
    for (int i = 0; i < M; i++)
        mini += A[i];

    maxi = 0;
    int n1 = N%M; //how many groups has size N/M + 1
    for (int i = 0; i < N; ) {
        maxi += A[i];
        if (n1 > 0) {
            i += (N/M + 1);
            n1 -= 1;
        } else
            i += (N/M);
    }

    printf("%lld %lld\n", mini, maxi);
}
