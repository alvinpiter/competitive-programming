#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 2000000000
#define MAXN 100000

/*
L[i] -> Smallest j, where j < i and S[j] > S[i]
R[i] -> Smallest j, where j > i and S[j] > S[i]
*/

int N, F[MAXN + 3], S[MAXN + 3], L[MAXN + 3], R[MAXN + 3];
LL M, sumF[MAXN + 3];

int main() {
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);

    scanf("%d%lld", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &F[i], &S[i]);
    }

    S[0] = S[N + 1] = INF;

    stack<int> stLeft;
    stLeft.push(0);

    for (int i = 1; i <= N; i++) {
        while (S[stLeft.top()] <= S[i])
            stLeft.pop();

        L[i] = stLeft.top();
        stLeft.push(i);
    }

    stack<int> stRight;
    stRight.push(N + 1);

    for (int i = N; i >= 1; i--) {
        while (S[stRight.top()] <= S[i])
            stRight.pop();

        R[i] = stRight.top();
        stRight.push(i);
    }

    sumF[0] = 0;
    for (int i = 1; i <= N; i++)
        sumF[i] = sumF[i - 1] + F[i];

    int miniSpiciness = INF;
    //treat S[i] as the maximum spiciness
    for (int i = 1; i <= N; i++) {
        LL sum = sumF[R[i] - 1] - sumF[L[i]];
        if (sum >= M)
            miniSpiciness = min(miniSpiciness, S[i]);
    }

    printf("%d\n", miniSpiciness);
}
