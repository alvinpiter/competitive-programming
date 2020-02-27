#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;

    scanf("%d%d", &n, &m);

    int matrix[n + 3][m + 3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
            matrix[i][j] -= (j + 1); //Normalize it. Each column should be like j, m + j, 2*m + j, etc
        }
    }

    int answer = 0;
    for (int j = 0; j < m; j++) {
        int ctr[n + 3]; //ctr[i] = how many numbers that will be in correct position after performing i cyclic shift on this column
        memset(ctr, 0, sizeof(ctr));

        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < 0 || matrix[i][j] % m != 0)
                continue;

            int targetPos = matrix[i][j]/m;

            if (targetPos >= n)
                continue;

            if (i < targetPos)
                ctr[n - (targetPos - i)] += 1;
            else
                ctr[i - targetPos] += 1;
        }

        int minCost = 1e9;
        for (int i = 0; i < n; i++)
            minCost = min(minCost, i + n - ctr[i]);

        answer += minCost;
    }

    printf("%d\n", answer);
}
