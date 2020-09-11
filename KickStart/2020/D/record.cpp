#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int T, prefixMax, N, numbers[MAXN + 3], answer;

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
            scanf("%d", &numbers[i]);

        prefixMax = -1;
        answer = 0;
        for (int i = 1; i <= N; i++) {
            if (numbers[i] > prefixMax && (i == N || numbers[i] > numbers[i + 1])) {
                answer += 1;
            }

            prefixMax = max(prefixMax, numbers[i]);
        }

        printf("Case #%d: %d\n", cases, answer);
    }
}
