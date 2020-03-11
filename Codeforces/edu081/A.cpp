#include<bits/stdc++.h>
using namespace std;

int t, n;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        if (n%2 == 0) {
            for (int i = 1; i <= n/2; i++)
                cout << 1;

            cout << endl;
        } else {
            cout << 7;
            for (int i = 1; i <= n/2 - 1; i++)
                cout << 1;

            cout << endl;
        }
    }
}
