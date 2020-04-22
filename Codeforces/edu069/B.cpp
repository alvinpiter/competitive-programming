#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[200003], posMax;

    scanf("%d", &n);

    posMax = 1;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] > a[posMax])
            posMax = i;
    }

    for (int i = 2; i <= posMax; i++) {
        if (a[i] < a[i - 1]) {
            printf("NO\n");
            return 0;
        }
    }

    for (int i = posMax + 1; i <= n; i++) {
        if (a[i] > a[i - 1]) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
}
