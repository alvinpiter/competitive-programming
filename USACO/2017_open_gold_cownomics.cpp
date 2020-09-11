#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 500
#define BASE 29
#define MOD 1299709

/*
Can be solved with some kind of sliding window too. Assume our window is currently in range l..r.
If the hashes is not disjoint, we should expand our window to l..r+1, because window l'..r (l' > l)
will also contain duplicate. This will reduce the complexity to O(NM).
*/

int id(char c) {
    return (c - 'A') + 1;
}

int N, M, ans;
pair<int, int> seen[MOD + 3];
char spotty[MAXN + 3][MAXN + 3], plain[MAXN + 3][MAXN + 3];

int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%s", spotty[i]);

    for (int i = 0; i < N; i++)
        scanf("%s", plain[i]);

    for (int i = 0; i < MOD; i++)
        seen[i] = {-1, -1};

    ans = M;
    int spottyHash[MAXN + 3], plainHash[MAXN + 3];
    for (int l = 0; l < M; l++) {
        for (int r = l; r < M; r++) {
            for (int i = 0; i < N; i++) {
                if (r == l) {
                    spottyHash[i] = id(spotty[i][r]);
                    plainHash[i] = id(plain[i][r]);
                } else {
                    spottyHash[i] = (spottyHash[i] * BASE + id(spotty[i][r]))%MOD;
                    plainHash[i] = (plainHash[i] * BASE + id(plain[i][r]))%MOD;
                }

                seen[spottyHash[i]] = {l, r};
            }

            bool uniq = true;
            for (int i = 0; i < N; i++) {
                if (seen[plainHash[i]] == make_pair(l, r)) {
                    uniq = false;
                    break;
                }
            }

            if (uniq)
                ans = min(ans, r - l + 1);
        }
    }

    printf("%d\n", ans);
}
