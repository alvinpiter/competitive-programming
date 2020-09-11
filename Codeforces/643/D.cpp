#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, S, answer[1000003];

    scanf("%d%d", &N, &S);

    if (S < 2 * N) {
        printf("NO\n");
        return 0;
    }

    for (int i = 0; i < N; i++)
        answer[i] = S/N;

    for (int i = 0; i < S%N; i++)
        answer[i] += 1;

    printf("YES\n");
    for (int i = 0; i < N; i++) {
        printf("%d", answer[i]);
        if (i == N - 1)
            printf("\n");
        else
            printf(" ");
    }
    printf("1\n");
}
