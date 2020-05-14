#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, x, a, gcd;

    cin >> n >> x;

    gcd = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        gcd = __gcd(gcd, a);
    }

    x = abs(x);
    if (x % gcd != 0)
        cout << "NO\n";
    else
        cout << "YES\n";
}
