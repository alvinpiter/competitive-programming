#include<bits/stdc++.h>
using namespace std;

int T, X, K;

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &X, &K);

        int cntPrime = 0;
        for (int i = 2; i * i <= X; i++) {
            while (X % i == 0) {
                cntPrime += 1;
                X /= i;
            }
        }

        if (X != 1)
            cntPrime += 1;

        if (cntPrime >= K)
            printf("1\n");
        else
            printf("0\n");
    }
}
