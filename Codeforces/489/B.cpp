#include<bits/stdc++.h>
using namespace std;

/*
Because gcd(a, b) = x, a and b can be rewritten as:
a = a' * x
b = b' * x

where a' and b' are coprime.

lcm(a, b) = y
(a * b)/x = y
(a' * x * b' * x)/x = y
a' * b' = y/x
*/

int main() {
    int l, r, x, y;

    cin >> l >> r >> x >> y;

    if (y % x != 0) {
        cout << 0 << endl;
        return 0;
    }

    int answer = 0;
    int target = y/x;
    for (int ap = 1; ap * ap <= target; ap++) {
        if (target % ap == 0) {
            int bp = target/ap;

            if (__gcd(ap, bp) == 1 && ap*x >= l && ap*x <= r && bp*x >= l && bp*x <= r) {
                answer += 1;
                if (ap != bp)
                    answer += 1;
            }
        }
    }

    cout << answer << endl;
}
