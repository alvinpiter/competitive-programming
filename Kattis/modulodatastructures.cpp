#include<bits/stdc++.h>
using namespace std;
#define SQRT 450
#define MAXN 200000

int N, Q, arr[MAXN + 3], sum[SQRT + 3][SQRT + 3]; //sum[a][b] -> total of updates at indices i, where i = a (modulo b)

int main() {
    scanf("%d%d", &N, &Q);

    memset(arr, 0, sizeof(arr));
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= Q; i++) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);

            if (b <= SQRT) {
                sum[a][b] += c;
            } else {
                for (int idx = a; idx <= N; idx += b)
                    arr[idx] += c;
            }
        } else {
            int d;
            scanf("%d", &d);

            int answer = arr[d];
            for (int b = 1; b <= SQRT; b++)
                answer += sum[d%b][b];

            printf("%d\n", answer);
        }
    }
}
