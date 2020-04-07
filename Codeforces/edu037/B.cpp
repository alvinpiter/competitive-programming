#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, l, r, currentTime, ans[1003];

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        currentTime = 0;
        for (int i = 1; i <= n; i++) {
            cin >> l >> r;
            if (l >= currentTime) {
                ans[i] = l;
                currentTime = l + 1;
            } else {
                if (currentTime > r) {
                    ans[i] = 0;
                } else {
                    ans[i] = currentTime;
                    currentTime += 1;
                }
            }
        }

        for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
}
