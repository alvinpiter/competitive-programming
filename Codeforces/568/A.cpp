#include<bits/stdc++.h>
using namespace std;

int main() {
    int a[3], d;

    cin >> a[0] >> a[1] >> a[2] >> d;

    sort(a, a + 3);

    int d1 = a[1] - a[0];
    int d2 = a[2] - a[1];

    if (d1 >= d && d2 >= d) {
        cout << 0 << endl;
    } else if (d1 >= d) {
        cout << d - d2 << endl;
    } else if (d2 >= d) {
        cout << d - d1 << endl;
    } else {
        cout << (d - d1) + (d - d2) << endl;
    }
}
