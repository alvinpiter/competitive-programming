#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

LL fact[1000003];

LL fastExponentiation(LL base, LL power) {
    if (power == 0) {
        return 1;
    }

    LL half = fastExponentiation(base, power/2);
    LL halfhalf = (half * half)%MOD;

    if (power % 2 == 0) {
        return halfhalf;
    } else {
        return (halfhalf * base)%MOD;
    }
}

void initFactorials() {
    fact[0] = 1;
    for (int i = 1; i <= 1000000; i++) {
        fact[i] = (fact[i - 1] * i)%MOD;
    }
}

LL C(int n, int k) {
    if (n < k) {
        return 0;
    }

    LL numerator = fact[n];
    LL denom1 = fastExponentiation(fact[n - k], MOD - 2);
    LL denom2 = fastExponentiation(fact[k], MOD - 2);

    LL answer = numerator;
    answer = (answer * denom1)%MOD;
    answer = (answer * denom2)%MOD;

    return answer;
}

int main() {
    int t, n, m, k, numbers[200003];

    initFactorials();

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) {
            cin >> numbers[i];
        }

        sort(numbers, numbers + n);

        LL answer = 0;
        for (int i = 0; i < n; i++) {
            int lb = lower_bound(numbers, numbers + n, numbers[i] - k) - numbers;
            int cnt = i - lb;

            answer = (answer + C(cnt, m - 1))%MOD;
        }

        cout << answer << endl;
    }
}
