#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int T, N;
bool princeIsMatched[MAXN + 3];

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);

        memset(princeIsMatched, false, sizeof(princeIsMatched));
        int unmatchedPrincess = -1;

        for (int i = 1; i <= N; i++) {
            int K;
            scanf("%d", &K);

            int matchPrince = -1;
            for (int j = 1; j <= K; j++) {
                int p;
                scanf("%d", &p);

                if (matchPrince == -1 && princeIsMatched[p] == false)
                    matchPrince = p;
            }

            if (matchPrince == -1) {
                unmatchedPrincess = i;
            } else {
                princeIsMatched[matchPrince] = true;
            }
        }

        if (unmatchedPrincess == -1) {
            printf("OPTIMAL\n");
        } else {
            int unmatchedPrince = -1;
            for (int i = 1; i <= N; i++) {
                if (princeIsMatched[i] == false) {
                    unmatchedPrince = i;
                    break;
                }
            }

            printf("IMPROVE\n");
            printf("%d %d\n", unmatchedPrincess, unmatchedPrince);
        }
    }
}
