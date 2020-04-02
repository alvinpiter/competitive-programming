#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, a, b;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> a >> b;

        if (a % b == 0)
            cout << 0 << endl;
        else
            cout << (a/b + 1)*b - a << endl;
    }
}
