#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000009

/*
First count the maximal number of correct answers such that there is no k consecutive correct answers.
This can be done greedily by grouping correct answers into group of size k - 1.

If there is leftOver, then we will need to "extend" (hence got combo) some of these (k - 1) consecutive answers.
*/

LL fastExponentiation(LL base, LL p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

int main() {
    LL n, m, k, leftOver;

    cin >> n >> m >> k;

    leftOver = m - ((n/k) * (k - 1) + n%k);
    if (leftOver <= 0) {
        cout << m << endl;
    } else {
        //sum of geometric sequence
        LL temp = 1;
        temp = (temp * (4 * k)%MOD)%MOD;
        temp = (temp * (fastExponentiation(2, leftOver - 1) - 1 + MOD)%MOD)%MOD;

        LL score = (2 * k + temp)%MOD;
        score = (score + (m - leftOver*k))%MOD;

        cout << score << endl;
    }
}
