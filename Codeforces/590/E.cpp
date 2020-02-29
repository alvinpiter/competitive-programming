#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n, m, x[MAXN + 3];
LL answer[MAXN + 3];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &x[i]);

    memset(answer, 0, sizeof(answer));

    answer[0] = 0;
    for (int i = 1; i < m; i++) {
        int l = min(x[i], x[i + 1]);
        int r = max(x[i], x[i + 1]);

        //All pj(n) where j < l
        if (l > 1) {
            answer[1] += (r - l);
            answer[l] -= (r - l);
        }

        //All pj(n) where j > r
        if (r < n)
            answer[r + 1] += (r - l);

        //All pj(n) where l < j < r
        if (l + 1 <= r - 1) {
            answer[l + 1] += (r - l - 1);
            answer[r] -= (r - l - 1);
        }

        //pl(n) and pr(n)
        if (l != r) {
            answer[l] += (r - 1);
            answer[l + 1] -= (r - 1);

            answer[r] += (l);
            answer[r + 1] -= (l);
        }
    }

    for (int i = 1; i <= n; i++) {
        answer[i] += answer[i - 1];
        cout << answer[i] << " ";
    }
    cout << endl;
}
