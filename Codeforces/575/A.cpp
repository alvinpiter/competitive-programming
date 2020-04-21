#include<bits/stdc++.h>
using namespace std;

int main() {
    int q;
    long long int a, b, c;

    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> a >> b >> c;
        cout << (a + b + c)/2 << endl;
    }
}
