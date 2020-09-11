#include<bits/stdc++.h>
using namespace std;
#define MAXA 2048

int main() {
    int q, n, counter[MAXA + 3];

    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> n;

        memset(counter, 0, sizeof(counter));
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;

            if (a <= MAXA)
                counter[a] += 1;
        }

        for (int i = 1; i <= MAXA/2; i++) {
            int pairs = counter[i]/2;
            counter[2 * i] += pairs;
        }

        if (counter[MAXA] > 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
