#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int t, n, e[MAXN + 3];

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &e[i]);

        sort(e + 1, e + n + 1);

        int answer = 0;
        for (int i = 1; i <= n; ) {
            int j;
            int maxi = 0;
            int cnt = 0;
            for (j = i; j <= n; j++) {
                maxi = max(maxi, e[j]);
                cnt += 1;

                if (cnt >= maxi) {
                    answer += 1;
                    break;
                }
            }

            i = j + 1;
        }

        printf("%d\n", answer);
    }
}
