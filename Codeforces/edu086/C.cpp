#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
WLOG, let's say a <= b.

(x mod a) mod b = (x mod b) mod a
x mod a = (x mod b) mod a

x and (x mod b) have the same remainder when divided by a, which means their difference is multiple of a.
Assume x = qb + r, where 0 <= r < b. Then qb is multiple of a and also multiple of LCM(a, b).

For each query, we want to exclude numbers with form qb + r (and qb is divible by a).
*/

int main() {
    int t, a, b, q;
    LL l, r;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> a >> b >> q;

        if (a > b)
            swap(a, b);

        LL lcm = (a * b)/__gcd(a, b);

        for (int query = 1; query <= q; query++) {
            cin >> l >> r;

            LL cnt = r/lcm - l/lcm;

            LL excluded = cnt * b;

            if (r%lcm < b)
                excluded -= b - (r%lcm + 1);

            if (l%lcm < b)
                excluded += b - l%lcm;

            if (query > 1)
                cout << " ";

            cout << (r - l + 1) - excluded;
        }

        cout << endl;
    }

}
