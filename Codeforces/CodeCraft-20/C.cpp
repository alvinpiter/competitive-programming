#include<bits/stdc++.h>
using namespace std;

int n, m, p, first, second;

int main() {
    scanf("%d%d%d", &n, &m, &p);

    first = -1;
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        if (a % p != 0 && first == -1){
            first = i;
        }
    }

    second = -1;
    for (int i = 0; i < m; i++) {
        int b;
        scanf("%d", &b);

        if (b % p != 0 && second == -1) {
            second = i;
        }
    }

    printf("%d\n", first + second);
}
