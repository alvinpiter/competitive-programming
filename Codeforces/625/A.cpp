#include<bits/stdc++.h>
using namespace std;

int n, r[103], b[103], count01, count10;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> r[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    count01 = count10 = 0;
    for (int i = 1; i <= n; i++) {
        if (r[i] == 1 && b[i] == 0)
            count10 += 1;
        else if (r[i] == 0 && b[i] == 1)
            count01 += 1;
    }

    if (count10 > 0) {
        int threshold = count01 + 1;
        cout << threshold/count10 + (threshold%count10 == 0 ? 0 : 1) << endl;
    } else
        cout << -1 << endl;
}
