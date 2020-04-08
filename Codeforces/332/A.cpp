#include<bits/stdc++.h>
using namespace std;

int main() {
    int d1, d2, d3;

    cin >> d1 >> d2 >> d3;

    int mn = min(d1 + d2 + d3, 2 * (d1 + d2));
    mn = min(mn, 2 * (d1 + d3));
    mn = min(mn, 2 * (d2 + d3));

    cout << mn << endl;
}
