#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 998244353
#define MAXN 200000

LL N, M, K, fact[MAXN + 3];

LL fastExponentiation(LL base, LL p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

LL C(LL n, LL k) {
    LL result = fact[n];

    result = (result * fastExponentiation(fact[k], MOD - 2))%MOD;
    result = (result * fastExponentiation(fact[n - k], MOD - 2))%MOD;

    return result;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i)%MOD;

    cin >> N >> M >> K;

    LL result = 0;
    for (int x = 0; x <= K; x++) {
        LL temp = C(N - 1, x); //choose x positions where the adjacent color is the same

        temp = (temp * M)%MOD; //there are M ways to paint the first block
        temp = (temp * fastExponentiation(M - 1, N - 1 - x))%MOD; //For every position where the adjacent color is different, there are (M -1) ways to choose the next color.

        result = (result + temp)%MOD;
    }

    cout << result << endl;
}
