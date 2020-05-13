#include<bits/stdc++.h>
using namespace std;

int main() {
    int q, l, r, d;

    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> l >> r >> d;

        int before = d;
        int after = (r/d + 1)*d;

        if (before < l)
            cout << before << endl;
        else
            cout << after << endl;
    }
}
