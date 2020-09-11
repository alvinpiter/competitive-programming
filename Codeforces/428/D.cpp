/*
Consider sample test case #2.

Subsets whose gcd is 2: {2}, {2, 4}, {2, 6}, {4, 6}, {2, 4, 6}. Each number in there contributes 2 to the answer.
So total contribution is 2*10 = 20

Do similar thing with subsets whose gcd is 3, 4, and 6.

Overall the answer is 20 + 9 + 4 + 6 = 39.

For each number d, we need to compute f[d] -> total size of subset of numbers whose gcd is g.
The final answer is sum(f[d] * d)

To calculate f[d], we can use inclusion-exclusion.
f[d] = g[d] - f[2*d] - f[3*d] - ...

g[d] is total size of subset whose numbers are divisble by d. It is formulated as:
sum(i * C(cnt[d], i)), where cnt[d] is number of numbers who is divisible by d.
Luckily, this sum can be simplified to cnt[d] * 2^(cnt[d] - 1). Hint for proof: k*C(n, k) = n*C(n - 1, k - 1).
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXA 1000000

LL fastExponentiation(LL base, int p) {
    if (p == 0)
        return 1;
    else if (p%2 == 0)
        return fastExponentiation((base * base)%MOD, p/2);
    else
        return (base * fastExponentiation((base * base)%MOD, p/2))%MOD;
}

int n, freq[MAXA + 3], cnt[MAXA + 3];
LL f[MAXA + 3], answer;

int main() {
    scanf("%d", &n);

    memset(freq, 0, sizeof(freq));
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        freq[a] += 1;
    }

    for (int divisor = 1; divisor <= MAXA; divisor++) {
        for (int i = divisor; i <= MAXA; i += divisor) {
            cnt[divisor] += freq[i];
        }
    }

    for (int g = MAXA; g >= 2; g--) {
        //Total size of subsets whose numbers are divisible by g
        f[g] = (fastExponentiation(2, cnt[g] - 1) * cnt[g])%MOD;

        for (int mul = 2 * g; mul <= MAXA; mul += g)
            f[g] = (f[g] - f[mul] + MOD)%MOD;
    }

    answer = 0;
    for (int g = 2; g <= MAXA; g++) {
        answer = (answer + (f[g] * g)%MOD)%MOD;
    }

    printf("%lld\n", answer);
}
