#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
Algorithm:
* Count occurence of each number and store it in variable cnt.
* Calculate the maximum number of cuts we can make with array t of length k. Do it with binary search. If we want to make x cut, we can take at most cnt[i]/x number i. If the total number of element we can take is >= k, then we try to increase x, otherwise decrease x.
* Construct the answer.
*/

int main() {
    int n, k, cnt[MAXN + 3], maxCut;
    vector<int> answer;

    scanf("%d%d", &n, &k);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        int s;
        scanf("%d", &s);

        cnt[s] += 1;
    }

    int lo = 1, hi = n, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        int len = 0;
        for (int i = 1; i <= MAXN; i++) {
            len += cnt[i]/mid;
        }

        if (len >= k)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    maxCut = hi;

    for (int i = 1; i <= MAXN; i++) {
        int take = min(k, cnt[i]/maxCut);
        for (int j = 1; j <= take; j++)
            answer.push_back(i);

        k -= take;
    }

    for (auto a: answer)
        printf("%d ", a);
    printf("\n");
}
