#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
Assume the split position are in p1, p2, p3, ...
Define sum(i) as sum of first i element.

The cost of the split can be formulated as:
k * sum(n) - (sum(p1) + sum(p2) + .. + sum(pk_1))

Hence we need to take the first k - 1 minimum sum(pi).
*/

int main() {
    int n, k;
    vector<LL> sums;
    LL prefixSum, answer;

    scanf("%d%d", &n, &k);

    prefixSum = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        prefixSum += a;
        if (i != n)
            sums.push_back(prefixSum);
    }

    sort(sums.begin(), sums.end());

    answer = prefixSum * k;
    for (int i = 0; i < k - 1; i++)
        answer -= sums[i];

    printf("%lld\n", answer);
}
