#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 998244353

LL fastExponentiation(LL base, LL p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p % 2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

int main() {
    LL N, M, L, R;

    cin >> N >> M >> L >> R;

    if ((N*M)%2 == 1)
        cout << fastExponentiation(R - L + 1, N * M) << endl;
    else {
        LL allWays = fastExponentiation(R - L + 1, N * M);

        LL invalidWays = fastExponentiation(R - L + 1, N * M);
        if ((R - L + 1)%2 == 1)
            invalidWays = (invalidWays - 1 + MOD)%MOD;

        invalidWays = (fastExponentiation(2, MOD - 2) * invalidWays)%MOD;

        LL validWays = (allWays - invalidWays + MOD)%MOD;

        cout << validWays << endl;
    }
}
