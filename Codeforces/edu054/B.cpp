#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    LL n;
    cin >> n;

    for (LL d = 2; ; d++) {
        if (n%d == 0) {
            if (d == 2)
                cout << n/2 << endl;
            else
                cout << 1 + (n - d)/2 << endl;

            return 0;
        }

        if (d * d > n)
            break;
    }

    //n is prime
    cout << 1 << endl;
}
