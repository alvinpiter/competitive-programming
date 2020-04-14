#include<bits/stdc++.h>
using namespace std;

int main() {
    int q, n, cnt[200003];

    scanf("%d", &q);
    for (int cases = 1; cases <= q; cases++) {
        scanf("%d", &n);

        for (int i = 1; i <= n; i++)
            cnt[i] = 0;

        for (int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);

            cnt[a] += 1;
        }

        vector<int> sortedCnt;
        for (int i = 1; i <= n; i++)
            sortedCnt.push_back(cnt[i]);

        sort(sortedCnt.begin(), sortedCnt.end());

        int answer = 0;
        int lastSize = n + 1;
        for (int i = sortedCnt.size() - 1; i >= 0; i--) {
            int take = min(sortedCnt[i], lastSize - 1);

            take = max(take, 0);

            answer += take;
            lastSize = take;
        }

        printf("%d\n", answer);
    }
}
