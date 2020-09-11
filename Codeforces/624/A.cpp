#include<bits/stdc++.h>
using namespace std;

int main () {
    int t, a, b;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> a >> b;
        if (a == b)
            cout << "0\n";
        else if (a < b) {
            if (a%2 == b%2)
                cout << "2\n";
            else
                cout << "1\n";
        } else {
            if (a%2 == b%2)
                cout << "1\n";
            else
                cout << "2\n";
        }
    }
}
