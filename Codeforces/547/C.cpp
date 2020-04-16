#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, p[200003];

    scanf("%d", &n);

    p[1] = 0;
    for (int i = 1; i < n; i++) {
        int q;
        scanf("%d", &q);

        p[i + 1] = q + p[i];
    }

    int mini = 1e9;
    for (int i = 1; i <= n; i++) mini = min(mini, p[i]);
    for (int i = 1; i <= n; i++) p[i] += (1 - mini); //normalize

    bool valid = true;
    bool seen[200003];
    memset(seen, false, sizeof(seen));

    for (int i = 1; i <= n; i++) {
        if (p[i] >= 1 && p[i] <= n)
            seen[p[i]] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (!seen[i])
            valid = false;
    }

    if (valid) {
        for (int i = 1; i <= n; i++)
            printf("%d ", p[i]);
        printf("\n");
    } else {
        printf("-1\n");
    }
}
