#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

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

LL C(int n, int k) {
    LL res = 1;
    for (int i = 1; i <= k; i++) {
        res = (res * (n - k + i))%MOD;
        res = (res * fastExponentiation(i, MOD - 2))%MOD;
    }

    return res;
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    LL all = (fastExponentiation(2, n) - 1 + MOD)%MOD;
    LL szA = C(n, a);
    LL szB = C(n, b);

    all = (all - szA + MOD)%MOD;
    all = (all - szB + MOD)%MOD;

    cout << all << endl;
}
