#include<bits/stdc++.h>
using namespace std;
#define MAXA 200000

int n;
vector<int> primes[MAXA + 3];

void factorize(int num) {
    for (int d = 2; d * d <= num; d++) {
        if (num % d == 0) {
            int cnt = 0;
            while (num%d == 0) {
                cnt += 1;
                num /= d;
            }

            primes[d].push_back(cnt);
        }
    }

    if (num != 1)
        primes[num].push_back(1);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        factorize(a);
    }

    long long int gcd = 1;
    for (int p = 2; p <= MAXA; p++) {
        sort(primes[p].begin(), primes[p].end());

        int first, second;
        if (primes[p].size() == n) {
            first = primes[p][0];
            second = primes[p][1];
        } else if (primes[p].size() == n - 1) {
            first = 0;
            second = primes[p][0];
        } else {
            first = 0;
            second = 0;
        }

        int cnt = max(first, second);
        for (int rep = 1; rep <= cnt; rep++)
            gcd = (gcd * p);
    }

    printf("%lld\n", gcd);
}
