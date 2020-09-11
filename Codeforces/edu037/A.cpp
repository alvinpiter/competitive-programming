#include<bits/stdc++.h>
using namespace std;

int main() {
    int tc, n, k, x[203];

    cin >> tc;
    for (int cases = 1; cases <= tc; cases++) {
        cin >> n >> k;
        for (int i = 1; i <= k; i++)
            cin >> x[i];

        int maxi = 0;
        for (int i = 2; i <= k; i++) {
            int gap = x[i] - x[i - 1] - 1;
            maxi = max(maxi, (gap + 1)/2 + 1);
        }

        maxi = max(maxi, x[1]);
        maxi = max(maxi, (n + 1) - x[k]);

        cout << maxi << endl;
    }
}
