#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 998244353
#define MAXN 200000

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

int N;
LL answer[MAXN + 3];

int main() {
    cin >> N;
    for (int sz = 1; sz < N; sz++) {
        LL firstCase = ((LL) 10 * 9 * fastExponentiation(10, N - sz - 1) * 2)%MOD;
        LL secondCase;

        if (sz + 2 <= N)
            secondCase = ((LL) 10 * 9 * 9 * fastExponentiation(10, N - sz - 2) * (N - sz - 1))%MOD;
        else
            secondCase = 0;

        answer[sz] = (firstCase + secondCase)%MOD;
    }

    answer[N] = 10;

    for (int i = 1; i <= N; i++)
        cout << answer[i] << " ";

    cout << endl;
}
