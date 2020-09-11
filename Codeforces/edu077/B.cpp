#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, a, b;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> a >> b;

        if (a > b)
            swap(a, b);

        if ((a + b)%3 == 0 && b <= 2 * a)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
