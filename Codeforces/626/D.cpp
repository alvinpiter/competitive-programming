#include<bits/stdc++.h>
using namespace std;
#define MAXLG 25

int n, a, ctr[MAXLG + 3], answer;
vector<int> suffix[MAXLG + 3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);

        int current = 0;
        for (int j = 0; j < MAXLG; j++) {
            if (a & (1 << j)) {
                current += (1 << j);
            }

            suffix[j].push_back(current);
        }
    }

    memset(ctr, 0, sizeof(ctr));
    for (int lg = 0; lg <= MAXLG; lg++) {
        sort(suffix[lg].begin(), suffix[lg].end());

        // 2^lg <= a + b < 2 * 2^lg
        for (int i = 0; i < suffix[lg].size(); i++) {
            int a = suffix[lg][i];
            int p1 = lower_bound(suffix[lg].begin() + (i + 1), suffix[lg].end(), (1 << lg) - a) - suffix[lg].begin();
            int p2 = lower_bound(suffix[lg].begin() + (i + 1), suffix[lg].end(), 2 * (1 << lg) - a) - suffix[lg].begin();

            ctr[lg] = (ctr[lg] + (p2 - p1))%2;
        }

        // 3 * 2^lg <= a + b < 4 * 2^lg
        for (int i = 0; i < suffix[lg].size(); i++) {
            int a = suffix[lg][i];
            int p1 = lower_bound(suffix[lg].begin() + (i + 1), suffix[lg].end(), 3 * (1 << lg) - a) - suffix[lg].begin();
            int p2 = lower_bound(suffix[lg].begin() + (i + 1), suffix[lg].end(), 4 * (1 << lg) - a) - suffix[lg].begin();

            ctr[lg] = (ctr[lg] + (p2 - p1))%2;
        }
    }

    answer = 0;
    for (int i = 0; i <= MAXLG; i++) {
        if (ctr[i] % 2 == 1)
            answer += (1 << i);
    }

    printf("%d\n", answer);
}
