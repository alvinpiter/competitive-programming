#include<bits/stdc++.h>
using namespace std;

int main() {
    //Days are numbered from 0, starting from Monday.
    //food[i] = food for day i. 0 means fish, 1 means rabbit, 2 means chicken.
    int food[7] = {0, 1, 2, 0, 2, 1, 0};
    int a, b, c, ans;

    cin >> a >> b >> c;

    ans = 0;
    for (int start = 0; start < 7; start++) {
        int aa = a, bb = b, cc = c;
        int cnt[3];
        memset(cnt, 0, sizeof(cnt));

        for (int d = start; d < 7; d++) {
            cnt[food[d]] += 1;
            if (cnt[0] <= aa && cnt[1] <= bb && cnt[2] <= cc)
                ans = max(ans, d - start + 1);
        }

        aa -= cnt[0];
        bb -= cnt[1];
        cc -= cnt[2];

        if (aa <= 0 || bb <= 0 || cc <= 0)
            continue;

        int numWeeks = min(aa/3, min(bb/2, cc/2));

        aa -= 3 * numWeeks;
        bb -= 2 * numWeeks;
        cc -= 2 * numWeeks;

        ans = max(ans, (7 - start) + 7 * numWeeks);

        memset(cnt, 0, sizeof(cnt));
        for (int prefix = 0; prefix < 7; prefix++) {
            cnt[food[prefix]] += 1;
            if (cnt[0] <= aa && cnt[1] <= bb && cnt[2] <= cc)
                ans = max(ans, (7 - start) + 7 * numWeeks + (prefix + 1));
        }
    }

    cout << ans << endl;
}
