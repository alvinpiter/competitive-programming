#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, cnt[1003], answer;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;

            cnt[a] += 1;
        }

        for (int sz = 1000; sz >= 1; sz--) {
            int count = 0;
            for (int i = sz; i <= 1000; i++) {
                count += cnt[i];
            }

            if (count >= sz) {
                answer = sz;
                break;
            }
        }

        cout << answer << endl;
    }
}
