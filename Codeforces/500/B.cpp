#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXV 1000000

int n, x, a[MAXN + 3], counter[MAXV + 3];

bool checkDuplicate() {
    for (int i = 0; i <= MAXV; i++) {
        if (counter[i] > 1)
            return true;
    }

    return false;
}

int main() {
    scanf("%d%d", &n, &x);

    memset(counter, 0, sizeof(counter));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        counter[a[i]] += 1;
    }

    if (checkDuplicate()) {
        printf("0\n");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if ((a[i] | x) != x) {
            if (counter[a[i] & x] > 0) {
                printf("1\n");
                return 0;
            }
        }
    }

    memset(counter, 0, sizeof(counter));
    for (int i = 1; i <= n; i++) {
        counter[a[i] & x] += 1;
    }

    if (checkDuplicate())
        printf("2\n");
    else
        printf("-1\n");
}
