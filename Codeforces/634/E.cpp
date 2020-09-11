#include<bits/stdc++.h>
using namespace std;

int t, n, prefixSum[203][200003];
vector<int> pos[203];

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);

        for (int i = 1; i <= 200; i++) {
            for (int j = 0; j <= n; j++)
                prefixSum[i][j] = 0;
        }

        for (int i = 1; i <= 200; i++) pos[i].clear();

        for (int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);

            pos[a].push_back(i);
            prefixSum[a][i] = 1;
        }

        for (int c = 1; c <= 200; c++) {
            for (int i = 1; i <= n; i++)
                prefixSum[c][i] += prefixSum[c][i - 1];
        }

        int answer = 1;
        for (int a = 1; a <= 200; a++) {
            int l = 0;
            int r = pos[a].size() - 1;

            while (r > l) {
                int maxi = 0;
                for (int b = 1; b <= 200; b++) maxi = max(maxi, prefixSum[b][pos[a][r] - 1] - prefixSum[b][pos[a][l]]);

                answer = max(answer, (l + 1)*2 + maxi);

                l += 1;
                r -= 1;
            }
        }

        printf("%d\n", answer);
    }
}
