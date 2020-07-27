#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000

int T, N, A[MAXN + 3], consUp, consDown, ans;

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
            scanf("%d", &A[i]);

        consUp = consDown = ans = 0;
        for (int i = 2; i <= N; i++) {
            if (A[i] > A[i - 1]) {
                consUp += 1;
                consDown = 0;
            }

            if (A[i] < A[i - 1]) {
                consDown += 1;
                consUp = 0;
            }

            if (consUp == 4 || consDown == 4) {
                ans += 1;
                consUp = consDown = 0;
            }
        }

        printf("Case #%d: %d\n", cases, ans);
    }

}
