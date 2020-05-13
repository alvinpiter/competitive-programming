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

int main() {
    LL x, k;

    cin >> x >> k;

    if (x == 0) {
        cout << 0 << endl;
        return 0;
    }

    LL answer = fastExponentiation(2, k);
    answer = (answer * (2 * x%MOD - 1) + MOD)%MOD;
    answer = (answer + 1)%MOD;

    cout << answer << endl;
}
