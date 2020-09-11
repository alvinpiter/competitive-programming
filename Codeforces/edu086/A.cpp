#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
Observations:
* Operation 2 which increases both numbers is useless.
* Operation 1 which increases one number is useless.
*/

int main() {
    int t;
    LL x, y, a, b;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> x >> y >> a >> b;

        if (x > y)
            swap(x, y);

        cout << (y - x)*a + min(2*x*a, x*b) << endl;
    }
}
