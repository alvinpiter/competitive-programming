#include<bits/stdc++.h>
using namespace std;
#define LL long long int

LL X, mini, ansA, ansB;

int main() {
    cin >> X;

    mini = 1e18;
    for (LL a = 1; a * a <= X; a++) {
        if (X % a != 0) continue;

        LL b = X/a;
        LL lcm = (a/__gcd(a, b))*b;

        if (lcm == X && max(a, b) < mini) {
            mini = max(a, b);
            ansA = a;
            ansB = b;
        }
    }

    cout << ansA << " " << ansB << endl;
}
