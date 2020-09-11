#include<bits/stdc++.h>
using namespace std;
#define LL long long int

/*
Assume we use operation 2 x times. Then:
(1 + 2 + .. + x) - (n - x) = k
*/

LL n, k;

int main() {
    cin >> n >> k;

    for (LL x = 1; x <= 100000; x++) {
        if ((x * x + x)/2 - (n - x) == k) {
            cout << n - x << endl;
            return 0;
        }
    }
}
