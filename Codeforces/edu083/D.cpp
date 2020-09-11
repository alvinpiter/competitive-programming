#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000
#define MOD 998244353

int n, m;
LL fact[MAXN + 3];

LL fastExpo(LL base, LL p) {
    if (p == 0)
        return 1;

    LL half = fastExpo(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

LL C(int n, int k) {
    LL result;

    result = fact[n];
    result = (result * fastExpo(fact[n - k], MOD - 2))%MOD;
    result = (result * fastExpo(fact[k], MOD - 2))%MOD;

    return result;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i)%MOD;

    cin >> n >> m;
    if (n == 2)
        cout << 0 << endl;
    else if (n == 3)
        cout << C(m, 2) << endl;
    else {
        LL answer = C(m, n - 1);
        answer = (answer * (n - 2))%MOD;
        answer = (answer * fastExpo(2, n - 3))%MOD;

        cout << answer << endl;
    }
}
