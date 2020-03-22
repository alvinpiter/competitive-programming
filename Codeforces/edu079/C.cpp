#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define LL long long int

int main() {
    int T, N, M, pos[MAXN + 3], b[MAXN + 3];

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; i++) {
            int a;
            scanf("%d", &a);

            pos[a] = i;
        }

        for (int i = 1; i <= M; i++)
            scanf("%d", &b[i]);

        LL answer = 0;
        for (int i = 1; i <= M; ){
            int j;
            for (j = i; j <= M; j++) {
                if (pos[b[j]] > pos[b[i]])
                    break;
            }

            answer += (LL) 2 * (pos[b[i]] - 1 - (i - 1)) + 1 + (j - i - 1);

            i = j;
        }

        printf("%lld\n", answer);
    }
}
