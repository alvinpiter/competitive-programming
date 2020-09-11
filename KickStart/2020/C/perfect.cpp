#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000
#define MAXA 100
#define OFFSET 10000000

int T, N, prefixSum, cnt[2 * OFFSET + 3];
LL answer;

int main() {
    scanf("%d", &T);

    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);
        for (int i = -MAXA*N; i <= MAXA*N; i++)
            cnt[i + OFFSET] = 0;

        prefixSum = 0;
        cnt[prefixSum + OFFSET] = 1;

        answer = 0;
        for (int i = 1; i <= N; i++) {
            int num;
            scanf("%d", &num);

            prefixSum += num;

            for (int j = 0; prefixSum - j * j >= -MAXA*N; j++) {
                answer += cnt[prefixSum - j * j + OFFSET];
            }

            cnt[prefixSum + OFFSET] += 1;
        }

        printf("Case #%d: %lld\n", cases, answer);
    }
}
