#include<bits/stdc++.h>
using namespace std;

int t, h, m;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> h >> m;
        cout << 24 * 60 - (h * 60 + m) << endl;
    }
}
