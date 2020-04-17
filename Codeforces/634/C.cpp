#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
int main() {
    int t, n, a[MAXN + 3];
    vector<int> cnt;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        sort(a, a + n);

        cnt.clear();

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

        int answer = 0;
        for (int i = 0; i < (int) cnt.size(); i++) {
            int cntCurrent = cnt[i];
            int cntOther = (int) cnt.size() - 1;

            answer = max(answer, min(cntCurrent, cntOther));
            answer = max(answer, min(cntCurrent - 1, cntOther + 1));
        }

        printf("%d\n", answer);
    }
}
