#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 300000

/*
WLOG, let's say x <= y <= z. In order to minimize the cost function, for a fixed y, we want x and y to be as close as possible to y.

Let's sort the pairs (weight, color) in non-decreasing order of weight.
For each index, we calculate:
* left[c][i] as largest index j (j < i) such that pair[j] has color c.
* right[c][i] as smallest index j (j > i) such that pair[j] has color c

After this, we just bruteforce on y.
*/

int main() {
    int t, n, sz[3], left[3][MAXN + 3], right[3][MAXN + 3];
    vector<pair<int, int> > weights;

    scanf("%d", &t);

    for (int cases = 1; cases <= t; cases++) {
        weights.clear();

        for (int c = 0; c < 3; c++)
            scanf("%d", &sz[c]);

        for (int c = 0; c < 3; c++) {
            for (int i = 0; i < sz[c]; i++) {
                int w;
                scanf("%d", &w);
                weights.push_back({w, c});
            }
        }

        sort(weights.begin(), weights.end());

        n = (int) weights.size();
        for (int c = 0; c < 3; c++) {
            int last;

            last = -1;
            for (int i = 0; i < n; i++) {
                left[c][i] = last;
                if (weights[i].second == c)
                    last = i;
            }

            last = -1;
            for (int i = n - 1; i >= 0; i--) {
                right[c][i] = last;
                if (weights[i].second == c)
                    last = i;
            }
        }

        LL answer = (LL) 8 * 1e18;
        for (int i = 0; i < n; i++) {
            int c = weights[i].second;

            for (int cl = 0; cl < 3; cl++) {
                for (int cr = 0; cr < 3; cr++) {
                    if (c != cl && c != cr && cl != cr && left[cl][i] != -1 && right[cr][i] != -1) {
                        LL x = weights[left[cl][i]].first;
                        LL y = weights[i].first;
                        LL z = weights[right[cr][i]].first;
                        LL cost = (x - y)*(x - y) + (x - z)*(x - z) + (y - z)*(y - z);

                        answer = min(answer, cost);
                    }
                }
            }
        }

        printf("%lld\n", answer);
    }
}
