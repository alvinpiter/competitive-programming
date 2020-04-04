#include<bits/stdc++.h>
using namespace std;
#define MAXN 100

int main() {
    int t, n, x, cnt[2 * MAXN + 3], a;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> x;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) {
            cin >> a;
            cnt[a] += 1;
        }

        for (int v = 2 * MAXN; v >= 1; v--) {
            int need = 0;
            for (int i = 1; i <= v; i++) {
                if (cnt[i] == 0)
                    need += 1;
            }

            if (need <= x) {
                cout << v << endl;
                break;
            }
        }
    }
}
