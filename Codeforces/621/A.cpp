#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, d, a[103];

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> d;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];

            if (i > 1) {
                int canTake = d/(i - 1);
                int take = min(canTake, a[i]);

                a[i] -= take;
                d -= (i - 1) * take;
                a[1] += take;
            }
        }

        cout << a[1] << endl;
    }
}
