#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, a, b;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> a >> b;

        int s = a + b;
        s = min(s, max(2 * b, a));
        s = min(s, max(2 * a, b));

        cout << s * s << endl;
    }
}
