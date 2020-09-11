#include<bits/stdc++.h>
using namespace std;
#define MAXN 150000

int t, n, a[MAXN + 3], suffixMin[MAXN + 3], answer;

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        suffixMin[n] = a[n];
        for (int i = n - 1; i >= 1; i--)
            suffixMin[i] = min(suffixMin[i + 1], a[i]);

        answer = 0;
        for (int i = 1; i < n; i++) {
            if (a[i] > suffixMin[i + 1])
                answer += 1;
        }

        printf("%d\n", answer);
    }
}
