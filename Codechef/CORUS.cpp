#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int main() {
    int T, N, Q, C, occ[26];
    char S[MAXN + 3];

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &Q);
        scanf("%s", S);

        memset(occ, 0, sizeof(occ));

        for (int i = 0; i < N; i++)
            occ[S[i] - 'a'] += 1;

        for (int q = 1; q <= Q; q++) {
            scanf("%d", &C);

            int ans = 0;
            for (int i = 0; i < 26; i++)
                ans += max(0, occ[i] - C);

            printf("%d\n", ans);
        }
    }
}
