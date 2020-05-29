#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
Observation: gcd(a + k, b + k) = gcd(a + k, b - a), which means that the gcd must be one of (b - a)'s divisor.
*/

LL a, b, delta;

int main() {
    cin >> a >> b;

    if (a > b)
        swap(a, b);

    delta = b - a;

    if (delta == 0) {
        cout << 0 << endl;
    } else {
        pair<LL, LL> best = {1e18, 1e18}; //{minLCM, minK}

        for (int div = 1; div * div <= delta; div++) {
            if (delta % div == 0) {
                LL k1 = (a/div + (a%div == 0 ? 0 : 1))*div - a;
                LL lcm1 = ((a + k1)/__gcd(a + k1, b + k1))*(b + k1);

                LL k2 = (a/(delta/div) + (a%(delta/div) == 0 ? 0 : 1))*(delta/div) - a;
                LL lcm2 = ((a + k2)/__gcd(a + k2, b + k2))*(b + k2);

                best = min(best, make_pair(lcm1, k1));
                best = min(best, make_pair(lcm2, k2));
            }
        }

        cout << best.second << endl;
    }
}
