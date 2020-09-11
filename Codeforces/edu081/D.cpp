/*
Find number of b such that gcd(a, m) = gcd(b, m), where a <= b < a + m

Let's say gcd(a, m) = g

We can break down b and m to:
b = x * g
m = y * g;

Since y is fixed, we have to find x that is co-prime to y and a <= x * g < a + m
We can do this by inclusion-exclusion principle
*/
#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int T;
LL a, m, g, loX, hiX, y;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> a >> m;

        g = __gcd(a, m);

        loX = a/g + (a%g == 0 ? 0 : 1);
        hiX = (a + m)/g - ((a + m)%g == 0 ? 1 : 0);

        y = m/g;

        vector<LL> primes; //all primes that divides y
        for (LL div = 2; div * div <= y; div++) {
            if (y % div == 0) {
                primes.push_back(div);
                while (y%div == 0) y /= div;
            }
        }

        if (y != 1)
            primes.push_back(y);

        LL countDivisible = 0;
        int nPrimes = primes.size();
        for (int mask = 1; mask < (1 << nPrimes); mask++) {
            LL gcd = 0;
            LL lcm = -1;
            int countOnBit = 0;
            for (int i = 0; i < nPrimes; i++) {
                if (mask & (1 << i)) {
                    gcd = __gcd(gcd, primes[i]);
                    lcm = (lcm == -1 ? primes[i] : (primes[i] * lcm)/gcd);
                    countOnBit += 1;
                }
            }

            //Count how many numbers from loX to hiX that is divisible by lcm
            LL lo = loX/lcm + (loX%lcm == 0 ? 0 : 1);
            LL hi = hiX/lcm;
            LL count = hi - lo + 1;

            //Inclusion-exclusion
            if (countOnBit%2 == 1)
                countDivisible += count;
            else
                countDivisible -= count;
        }

        cout << (hiX - loX + 1) - countDivisible << endl;
    }
}
