#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000
#define LL long long int

int n;
LL m[MAXN + 3], prefixCost[MAXN + 3], suffixCost[MAXN + 3];
stack<int> prefixStack, suffixStack;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &m[i]);
    }

    m[0] = m[n + 1] = 0;

    prefixCost[0] = 0;
    prefixStack.push(0);
    for (int i = 1; i <= n; i++) {
        while (m[i] <= m[prefixStack.top()])
            prefixStack.pop();

        int j = prefixStack.top();
        prefixCost[i] = prefixCost[j] + (LL) m[i] * (i - j);

        prefixStack.push(i);
    }

    suffixCost[n + 1] = 0;
    suffixStack.push(n + 1);
    for (int i = n; i >= 1; i--) {
        while (m[i] <= m[suffixStack.top()])
            suffixStack.pop();

        int j = suffixStack.top();
        suffixCost[i] = suffixCost[j] + (LL) m[i] * (j - i);

        suffixStack.push(i);
    }

    LL best = 0;
    int bestIndex;
    for (int i = 1; i <= n; i++) {
        LL score = prefixCost[i] + suffixCost[i] - m[i];
        if (score > best) {
            best = score;
            bestIndex = i;
        }
    }

    int currentIndex;

    currentIndex = bestIndex - 1;
    while (currentIndex > 0) {
        m[currentIndex] = min(m[currentIndex], m[currentIndex + 1]);
        currentIndex -= 1;
    }

    currentIndex = bestIndex + 1;
    while (currentIndex <= n) {
        m[currentIndex] = min(m[currentIndex], m[currentIndex - 1]);
        currentIndex += 1;
    }

    for (int i = 1; i <= n; i++)
        cout << m[i] << " ";

    cout << endl;
}
