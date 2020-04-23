#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);

        if (n == 1) {
            printf("-1\n");
        } else {
            printf("2");
            for (int i = 2; i <= n; i++)
                printf("3");
            printf("\n");
        }
    }
}
