#include<bits/stdc++.h>
using namespace std;

int t, n, a, sum;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        sum = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a;
            sum += a;
        }

        cout << (sum/n + (sum%n == 0 ? 0 : 1)) << endl;
    }
}
