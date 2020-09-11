#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 100000

int N, K, A[MAXN + 3];
LL fact[MAXN + 3];

LL fastExponentiation(int base, int p) {
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
    LL numerator = fact[n];
    LL denominator = (fact[k] * fact[n - k])%MOD;
    return (numerator * fastExponentiation(denominator, MOD - 2))%MOD;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i)%MOD;

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    sort(A + 1, A + N + 1);

    LL answer = 0;

    //Count contribution of A[i] as the maximum element
    for (int i = K; i <= N; i++) {
        LL contribution = (C(i - 1, K - 1) * A[i])%MOD;
        answer = (answer + contribution)%MOD;
    }

    //Count contribution of A[i] as the minimum element
    for (int i = 1; i <= N - K + 1; i++) {
        LL contribution = (C(N - i, K - 1) * A[i])%MOD;
        answer = (answer - contribution + MOD)%MOD;
    }

    cout << answer << endl;
}
