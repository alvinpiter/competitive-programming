#include<bits/stdc++.h>
using namespace std;

int main() {
    int q, c, m, x, count;

    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> c >> m >> x;

        count = min(c, min(m, x));

        c -= count;
        m -= count;

        count += min((c + m)/3, min(c, m));

        cout << count << endl;
    }
}
