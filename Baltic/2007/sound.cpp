#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000

int main() {
    int n, m, c, a[MAXN + 3], cnt;
    deque<int> miniWindow, maxiWindow;

    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    cnt = 0;
    for (int i = 1; i <= n; i++) {
        while (!miniWindow.empty() && miniWindow.front() <= i - m)
            miniWindow.pop_front();

        while (!miniWindow.empty() && a[i] <= a[miniWindow.back()])
            miniWindow.pop_back();

        miniWindow.push_back(i);

        while (!maxiWindow.empty() && maxiWindow.front() <= i - m)
            maxiWindow.pop_front();

        while (!maxiWindow.empty() && a[i] >= a[maxiWindow.back()])
            maxiWindow.pop_back();

        maxiWindow.push_back(i);

        if (i >= m && a[maxiWindow.front()] - a[miniWindow.front()] <= c) {
            cnt += 1;
            printf("%d\n", i - m + 1);
        }
    }

    if (cnt == 0) {
        printf("NONE\n");
    }
}
