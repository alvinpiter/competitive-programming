#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[100003], numPrime;
    bool prime[100003];

    cin >> n;

    memset(prime, true, sizeof(prime));
    numPrime = 0;
    for (int i = 2; i <= n; i++) {
        if (prime[i]) {
            numPrime += 1;

            a[i] = numPrime;
            for (int j = 2 * i; j <= n; j += i) {
                prime[j] = false;
                a[j] = numPrime;
            }
        }
    }

    for (int i = 2; i <= n; i++)
        cout << a[i] << " ";

    cout << endl;
}
