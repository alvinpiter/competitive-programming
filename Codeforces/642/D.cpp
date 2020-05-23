#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int t, n, answer[MAXN + 3];

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);

        priority_queue<pair<int, int> > pq; //{length, -start}

        pq.push({n, -1});

        int step = 0;
        while (!pq.empty()) {
            auto top = pq.top(); pq.pop();

            int length = top.first;
            int l = -top.second, r = l + length - 1;

            if (length % 2 == 1) {
                int idx = (l + r)/2;
                answer[idx] = ++step;

                if (length != 1) {
                    pq.push({length/2, -l});
                    pq.push({length/2, -(idx + 1)});
                }
            } else {
                int idx = (l + r - 1)/2;
                answer[idx] = ++step;

                if (length > 2)
                    pq.push({length/2 - 1, -l});

                pq.push({length/2, -(idx + 1)});
            }
        }

        for (int i = 1; i <= n; i++) {
            printf("%d", answer[i]);
            if (i == n)
                printf("\n");
            else
                printf(" ");
        }
    }
}
