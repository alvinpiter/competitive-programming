#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 200000

/*
Brute force on number of empty rooms.
All number of empty rooms x will be reachable as long as x <= k and x < n.
*/

LL fastExponentiation(LL base, int p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

LL fact[MAXN + 3];

LL C(int n, int k) {
    if (k > n)
        return 0;

    LL numerator = fact[n];
    LL denomintator = fastExponentiation((fact[k] * fact[n - k])%MOD, MOD - 2);
    return (numerator * denomintator)%MOD;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i)%MOD;

    int n, k;
    cin >> n >> k;

    LL answer = 0;

    //There is at most min(n - 1, k) empty room
    for (int numEmpty = 0; numEmpty <= min(n - 1, k); numEmpty++) {
        LL waysToChooseEmptyRoom = C(n, numEmpty); //number of ways to choose empty rooms

        int numNonEmpty = n - numEmpty;
        int numToSpread = numEmpty;
        LL waysToSpread = C(numToSpread + numNonEmpty - 1, numNonEmpty - 1); //number of ways to spread the people to non-empty rooms

        answer += (waysToChooseEmptyRoom * waysToSpread)%MOD;
        answer %= MOD;
    }

    cout << answer << endl;
}
