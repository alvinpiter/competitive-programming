#include<bits/stdc++.h>
using namespace std;

int main() {
    int T, N, X[10];

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
            scanf("%d", &X[i]);

        X[N + 1] = 100; //dummy

        int currentSize = 1;
        int miniSize = N;
        int maxiSize = 0;
        for (int i = 2; i <= N + 1; i++) {
            if (X[i] - X[i - 1] <= 2)
                currentSize += 1;
            else {
                miniSize = min(miniSize, currentSize);
                maxiSize = max(maxiSize, currentSize);
                currentSize = 1;
            }
        }

        printf("%d %d\n", miniSize, maxiSize);
    }
}
