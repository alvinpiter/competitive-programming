#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
Algorithm:
* Calculate the occurence of each number and sort it in non-decreasing order. Name this sorted occurence array as cnt.
* Observe that the number of contest is small (because the number of problems double). Let's assume the number of contest is 20.
* From each index i in cnt, we will try to make a contest starting from it. The total number of problems depends on the base (number of problems in first contest) and number of contest. Everytime we add a new contest we re-calculate the maximum new base, it's equal to min(cnt[j]/2^(j - i)).

Total complexity is O(n log n).
*/

int main() {
    int n, a[MAXN + 3], p2[22];
    vector<int> cnt;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    sort(a, a + n);

    //construct cnt array
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1])
            count += 1;
        else {
            cnt.push_back(count);
            count = 1;
        }
    }
    cnt.push_back(count);

    sort(cnt.begin(), cnt.end());

    //precalculate 2^i
    p2[0] = 1;
    for (int i = 1; i <= 20; i++)
        p2[i] = 2 * p2[i - 1];

    //bruteforce starting position
    int ans = 0;
    for (int i = 0; i < (int) cnt.size(); i++) {
        int base = 1e9;
        for (int j = i; j < min((int) cnt.size(), i + 20); j++) {
            base = min(base, cnt[j]/p2[j - i]);
            ans = max(ans, base * (p2[j - i + 1] - 1));
        }
    }

    printf("%d\n", ans);
}
