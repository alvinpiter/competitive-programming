#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int t, n, a[100003];
LL prefixSum, suffixSum;

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);

        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        prefixSum = 0;
        bool nonPositivePrefixExist = false;
        for (int i = 1; i < n; i++) {
            prefixSum += a[i];
            if (prefixSum <= 0)
                nonPositivePrefixExist = true;
        }

        suffixSum = 0;
        bool nonPositiveSuffixExist = false;
        for (int i = n; i > 1; i--) {
            suffixSum += a[i];
            if (suffixSum <= 0)
                nonPositiveSuffixExist = true;
        }

        if (nonPositivePrefixExist || nonPositiveSuffixExist)
            printf("NO\n");
        else
            printf("YES\n");
    }
}
