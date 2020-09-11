#include<bits/stdc++.h>
using namespace std;

int t, n, k;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> k;
        if (n%k <= k/2) {
            cout << n << endl;
        } else {
            cout << n - (n%k - k/2) << endl;
        }
    }
}
