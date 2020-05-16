#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000

//Find subarray such that there is no -i and i (in that order)
//nxt[i] -> smallest index j such that a[j] = i
int n, a[MAXN + 3], nxt[MAXN + 3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++)
        nxt[i] = n + 1;

    vector<int> answer;
    int rightMost = n + 1;
    for (int i = n; i >= 1; i--) {
        if (a[i] < 0)
            rightMost = min(rightMost, nxt[-a[i]]);

        if (a[i] > 0)
            nxt[a[i]] = i;

        answer.push_back(rightMost - i);
    }

    reverse(answer.begin(), answer.end());
    for (auto a: answer)
        printf("%d ", a);
    printf("\n");
}
