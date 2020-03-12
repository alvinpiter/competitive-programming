#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, a, countOdd, countEven;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        countOdd = countEven = 0;
        for (int i = 0; i < n; i++) {
            cin >> a;
            if (a%2 == 0)
                countEven += 1;
            else
                countOdd += 1;
        }

        if (countOdd == n || countEven == n)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
