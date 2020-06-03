#include<bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c, d, e, f;

    cin >> a >> b >> c;
    cin >> d >> e >> f;

    cout << max(0, d - a) + max(0, e - b) + max(0, f - c) << endl;
}
