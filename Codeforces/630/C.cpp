#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int t, n, k, cnt[26];
char s[MAXN + 3];

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d", &n, &k);
        scanf("%s", s);

        int answer = 0;
        int l = 0, r = k - 1;

        while (l <= r) {
            memset(cnt, 0, sizeof(cnt));

            for (int i = l; i < n; i += k)
                cnt[s[i] - 'a'] += 1;

            if (l != r) {
                for (int i = r; i < n; i += k)
                    cnt[s[i] - 'a'] += 1;
            }

            int total = (l == r ? n/k : 2 * n/k);
            int maxi = 0;

            for (int i = 0; i < 26; i++) maxi = max(maxi, cnt[i]);

            answer += (total - maxi);

            l += 1;
            r -= 1;
        }

        printf("%d\n", answer);
    }
}
