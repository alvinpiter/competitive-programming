#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 10000
#define MAXA 1000000

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

int n, a[MAXN + 3];
int cnt[MAXA + 3]; //to calculate lcm

int main() {
    cin >> n;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];

        int temp = a[i];
        for (int d = 2; d * d <= temp; d++) {
            if (temp % d == 0) {
                int count = 0;
                while (temp % d == 0) {
                    count += 1;
                    temp /= d;
                }

                cnt[d] = max(cnt[d], count);
            }
        }

        if (temp != 1)
            cnt[temp] = max(cnt[temp], 1);
    }

    LL lcm = 1;
    for (int i = 1; i <= MAXA; i++)
        lcm = (lcm * fastExponentiation(i, cnt[i]))%MOD;

    LL answer = 0;
    for (int i = 1; i <= n; i++) {
        LL b = (lcm * fastExponentiation(a[i], MOD - 2))%MOD;
        answer = (answer + b)%MOD;
    }

    cout << answer << endl;
}
