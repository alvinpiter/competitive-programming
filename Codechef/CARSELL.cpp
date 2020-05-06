#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MOD 1000000007

int T, N, P[MAXN + 3], answer;

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
            scanf("%d", &P[i]);

        sort(P + 1, P + N + 1);
        reverse(P + 1, P + N + 1);

        answer = 0;
        for (int i = 1; i <= N; i++) {
            P[i] = max(0, P[i] - i + 1);
            answer = (answer + P[i])%MOD;
        }

        printf("%d\n", answer);
    }
}
