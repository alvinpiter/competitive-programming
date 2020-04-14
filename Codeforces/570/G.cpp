#include<bits/stdc++.h>
using namespace std;

int main() {
    int q, n, cnt[200003], cnt1[200003];

    scanf("%d", &q);
    for (int cases = 1; cases <= q; cases++) {
        scanf("%d", &n);

        for (int i = 1; i <= n; i++) {
            cnt[i] = cnt1[i] = 0;
        }

        for (int i = 1; i <= n; i++) {
            int a, f;
            scanf("%d%d", &a, &f);

            cnt[a] += 1;
            if (f == 1)
                cnt1[a] += 1;
        }

        vector<pair<int, int> > sortedCnt; //{cnt, cnt1}
        for (int i = 1; i <= n; i++)
            sortedCnt.push_back({cnt[i], cnt1[i]});

        sort(sortedCnt.begin(), sortedCnt.end());

        int answer1 = 0;
        int answer2 = 0;

        priority_queue<pair<int, int> > pq;
        for (int sz = n; sz >= 1; sz--) {
            while (!sortedCnt.empty() && sortedCnt.back().first >= sz) {
                auto back = sortedCnt.back();

                pq.push({back.second, back.first});
                sortedCnt.pop_back();
            }

            if (pq.empty()) continue;

            auto top = pq.top(); pq.pop();

            answer1 += sz;
            answer2 += min(sz, top.first);
        }

        printf("%d %d\n", answer1, answer2);
    }
}
