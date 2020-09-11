#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
Observations:
* If we can do it by convincing x people, then we can do it by convincing x - 1 people
* It is better to convince people consecutively (dont skip people who has not reviewed)
*/

int main() {
    int n, m, a[MAXN + 3];
    bool reviewed[MAXN + 3];

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    int lo = 0, hi = n, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        int cntReview = 0;
        int cntConvinced = 0;

        for (int i = 1; i <= n; i++) {
            if (a[i] <= cntReview) {
                cntReview += 1;
            } else {
                if (cntConvinced < mid) {
                    cntConvinced += 1;
                    cntReview += 1;
                }
            }
        }

        if (cntReview >= m)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    cout << lo << endl;
}
