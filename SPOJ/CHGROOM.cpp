#include<bits/stdc++.h>
using namespace std;
#define LL long long int

LL q;
int primeCount;

int main() {
    cin >> q;

    primeCount = 0;
    for (LL i = 2; i * i <= q; i++) {
        while (q % i == 0) {
            primeCount += 1;
            q /= i;
        }
    }

    if (q != 1)
        primeCount += 1;

    if (primeCount == 0) {
        cout << "ANNE\n";
    } else if (primeCount == 1) {
        cout << "ANNE\n";
    } else if (primeCount == 2) {
        cout << "MARIAN\n";
    } else {
        cout << "ANNE\n";
    }
}
