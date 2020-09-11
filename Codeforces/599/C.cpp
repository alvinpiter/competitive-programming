#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    LL N, prime;
    int cntPrime;

    cin >> N;

    if (N == 1) {
        cout << 1 << endl;
    } else {
        cntPrime = 0;
        for (LL i = 2; i * i <= N; i++) {
            if (N % i == 0) {
                cntPrime += 1;
                prime = i;

                while (N%i == 0) N /= i;
            }
        }

        if (N != 1) {
            cntPrime += 1;
            prime = N;
        }

        if (cntPrime == 1)
            cout << prime << endl;
        else
            cout << 1 << endl;
    }
}
