#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 1000000

LL factorial[MAXN + 3];

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

LL C(LL n, LL k) {
    LL numerator = factorial[n];
    LL denominator = fastExponentiation((factorial[n - k] * factorial[k])%MOD, MOD - 2);
    return (numerator * denominator)%MOD;
}

int main() {
    factorial[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        factorial[i] = (factorial[i - 1] * i)%MOD;

    LL N, A, B, D;
    while (cin >> N >> A >> B >> D) {
        LL countSchools = C(N, A);
        LL countStudents = fastExponentiation(C(B, D), A);
        LL total = (countSchools * countStudents)%MOD;

        cout << total << endl;
    }
}
