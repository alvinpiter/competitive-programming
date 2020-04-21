#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[103];

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int d = 0; d <= 100; d++) {
        for (int target = 1; target <= 100; target++) {
            bool possible = true;
            for (int i = 1; i <= n; i++) {
                if (a[i] != target && a[i] + d != target && a[i] - d != target)
                    possible = false;
            }

            if (possible) {
                cout << d << endl;
                return 0;
            }
        }
    }

    cout << -1 << endl;
}
