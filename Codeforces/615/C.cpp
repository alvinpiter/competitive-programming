#include<bits/stdc++.h>
using namespace std;

int t, n, smallestDivisor, secondSmallestDivisor;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        smallestDivisor = -1;
        for (int i = 2; i * i <= n; i++) {
            if (n%i == 0) {
                smallestDivisor = i;
                break;
            }
        }

        if (smallestDivisor == -1) {
            cout << "NO\n";
            continue;
        }

        n /= smallestDivisor;

        secondSmallestDivisor = -1;
        for (int i = smallestDivisor + 1; i * i <= n; i++) {
            if (n%i == 0) {
                secondSmallestDivisor = i;
                break;
            }
        }

        if (secondSmallestDivisor == -1) {
            cout << "NO\n";
            continue;
        }

        n /= secondSmallestDivisor;
        if (n > secondSmallestDivisor)
            cout << "YES\n" << smallestDivisor << " " << secondSmallestDivisor << " " << n << endl;
        else
            cout << "NO\n";
    }
}
