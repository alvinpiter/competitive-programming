#include<bits/stdc++.h>
using namespace std;
#define LL long long int

LL q, k, n, a, b;

int main() {

    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> k >> n >> a >> b;

        if (k - n * b <= 0)
            cout << -1 << endl;
        else
            cout << min((k - n * b - 1)/(a - b), n) << endl;
    }
}
