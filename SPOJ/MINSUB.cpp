#include<bits/stdc++.h>
using namespace std;
#define MAXR 1000

int T, R, C, K, M[MAXR + 3][MAXR + 3];

int getMaxArea(int threshold) {
    int h[MAXR + 3][MAXR + 3];
    memset(h, 0, sizeof(h));

    int maxArea = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++)
            h[i][j] = (M[i][j] >= threshold ? 1 + h[i - 1][j] : 0);

        stack<int> stLeft, stRight;
        int leftOf[MAXR + 3], rightOf[MAXR + 3];

        h[i][0] = -1;
        stLeft.push(0);
        for (int j = 1; j <= C; j++) {
            while (h[i][stLeft.top()] >= h[i][j])
                stLeft.pop();

            leftOf[j] = stLeft.top();
            stLeft.push(j);
        }

        h[i][C + 1] = -1;
        stRight.push(C + 1);
        for (int j = C; j >= 1; j--) {
            while (h[i][stRight.top()] >= h[i][j])
                stRight.pop();

            rightOf[j] = stRight.top();
            stRight.push(j);
        }

        for (int j = 1; j <= C; j++) {
            int area = (rightOf[j] - leftOf[j] - 1) * h[i][j];
            maxArea = max(maxArea, area);
        }
    }

    return maxArea;
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d%d", &R, &C, &K);
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++)
                scanf("%d", &M[i][j]);
        }

        int lo = 1, hi = 1000000000, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (getMaxArea(mid) >= K)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        printf("%d %d\n", hi, getMaxArea(hi));
    }
}
