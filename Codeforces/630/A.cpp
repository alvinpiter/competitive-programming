#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, a, b, c, d, x, y, x1, y1, x2, y2, step;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> a >> b >> c >> d;
        cin >> x >> y >> x1 >> y1 >> x2 >> y2;

        if (x != x1 || x != x2) {
            step = min(a, b);
            a -= step;
            b -= step;
        }

        if (y != y1 || y != y2) {
            step = min(c, d);
            c -= step;
            d -= step;
        }

        if (a > x - x1 || b > x2 - x || c > y - y1 || d > y2 - y)
            cout << "No\n";
        else
            cout << "Yes\n";
    }
}
