#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int main() {
    int t, n, p[MAXN + 3];

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &p[i]);

        bool valid = true;
        for (int i = 2; i <= n; i++) {
            if (p[i] - p[i - 1] > 1)
                valid = false;
        }

        if (valid)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
