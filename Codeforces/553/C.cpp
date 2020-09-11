#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

LL sum(LL idx) {
    LL cntOdd = 0;
    LL cntEven = 0;
    LL result = 0;
    LL sz = 1;

    for (int stage = 1;; stage++) {
        LL l = cntEven + cntOdd + 1;
        LL r = min(idx, l + sz - 1);

        if (l > r)
            break;

        LL take = (r - l + 1);
        if (stage%2 == 1) {
            //sum of odds
            LL u1 = 2*(cntOdd) - 1 + 2;
            LL un = u1 + (take - 1)*2;

            LL temp = ((u1 + un)/2)%MOD;
            temp = (temp * (take%MOD))%MOD;

            result = (result + temp)%MOD;
            cntOdd += take;
        } else {
            //sum of evens
            LL u1 = 2*cntEven + 2;
            LL un = u1 + (take - 1)*2;

            LL temp = ((u1 + un)/2)%MOD;
            temp = (temp * (take%MOD))%MOD;

            result = (result + temp)%MOD;
            cntEven += take;
        }

        sz *= 2;
    }

    return result;
}

int main() {
    LL l, r;

    cin >> l >> r;
    cout << (sum(r) - sum(l - 1) + MOD)%MOD << endl;
}
