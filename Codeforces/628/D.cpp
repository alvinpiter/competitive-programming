#include<bits/stdc++.h>
using namespace std;
#define LL long long int

LL xorr, sum;

int main() {
    cin >> xorr >> sum;

    //no solution if parity is not the same or xorr is larger than sum
    if (xorr%2 != sum%2 || xorr > sum) {
        cout << "-1\n";
        return 0;
    }

    //the answer is 1 if xorr is equal to sum
    if (xorr == sum) {
        //exception when xorr is 0
        if (xorr == 0) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
            cout << xorr << endl;
        }
    } else {
        //Use identity a + b = a xor b + 2 * (a & b)

        LL andd = (sum - xorr)/2;

        if (((sum - andd)&andd) == andd) {
            cout << 2 << endl;
            cout << andd << " " << sum - andd << endl;
        } else {
            cout << 3 << endl;
            cout << xorr << " " << andd << " " << andd << endl;
        }
    }
}
