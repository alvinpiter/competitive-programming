#include<bits/stdc++.h>
using namespace std;

int n, m, a[200000 + 3];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    if (n > m) {
        printf("0\n");
    } else {
        int result = 1%m;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int num = abs(a[i] - a[j])%m;

                result = (result * num)%m;
            }
        }

        printf("%d\n", result);
    }
}
