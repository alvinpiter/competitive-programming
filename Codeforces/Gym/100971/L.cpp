#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int n, a[MAXN + 3], b[MAXN + 3];

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    sort(a, a + n);
    sort(b, b + n);

    int cntFirst = 0;
    int bound1 = n; //last opponent that first team can win against
    for (int i = n - 1; i >= 0; i--) {
        int pos = lower_bound(b, b + bound1, a[i]) - b;
        if (pos == 0)
            break;
        else {
            cntFirst += 1;
            bound1 = pos - 1;
        }
    }

    int cntSecond = 0;
    int bound2 = n; //last opponent that second team can win against
    for (int i = n - 1; i >= 0; i--) {
        int pos = lower_bound(a, a + bound2, b[i]) - a;
        if (pos == 0)
            break;
        else {
            cntSecond += 1;
            bound2 = pos - 1;
        }
    }


    bool firstCanWin = (2 * cntFirst > n);
    bool secondCanWin = (2 * cntSecond > n);

    if (firstCanWin && secondCanWin)
        printf("Both\n");
    else if (firstCanWin)
        printf("First\n");
    else if (secondCanWin)
        printf("Second\n");
    else
        printf("None\n");
}
