#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int N, s[MAXN + 3];
bool visited[MAXN + 3];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &s[i]);

    LL answer = 0;
    for (int C = 1; C < N - 1; C++) {
        LL currentProfit = 0;
        memset(visited, false, sizeof(visited));

        for (int k = 0; k * C < N - 1; k++) {
            if (N - 1 - k * C <= 1) break; //A must be > 1
            if (N - 1 - k * C - C < 1) break; //B must be > 0

            if (visited[N - 1 - k * C]) break;
            visited[N - 1 - k * C] = true;

            if (visited[k * C]) break;
            visited[k * C] = true;

            currentProfit += s[k * C];
            currentProfit += s[N - 1 - k * C];

            answer = max(answer, currentProfit);
        }
    }

    printf("%lld\n", answer);
}
