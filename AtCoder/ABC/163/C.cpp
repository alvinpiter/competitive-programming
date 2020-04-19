#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, cnt[200003];

    scanf("%d", &N);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 2; i <= N; i++) {
        int A;
        scanf("%d", &A);

        cnt[A] += 1;
    }

    for (int i = 1; i <= N; i++)
        printf("%d\n", cnt[i]);
}
