#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[200003], b[200003], x[200003];

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);

    a[1] = b[1];
    x[1] = 0;
    for (int i = 2; i <= n; i++) {
        x[i] = max(x[i - 1], a[i - 1]);
        a[i] = b[i] + x[i];
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
