#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, m;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d", &n, &m);

        if (n == 1)
            printf("0\n");
        else if (n == 2)
            printf("%d\n", m);
        else
            printf("%d\n", 2 * m);
    }
}
