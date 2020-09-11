#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
endd[i] = longest increasing subsegment ending at i
start[i] = longest increasing subsegment starting at i
*/
int n, a[MAXN + 3], endd[MAXN + 3], start[MAXN + 3];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    endd[0] = 0;
    endd[1] = 1;
    for (int i = 2; i <= n; i++) {
        endd[i] = (a[i] > a[i - 1] ? 1 + endd[i - 1] : 1);
    }

    start[n + 1] = 0;
    start[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        start[i] = (a[i] < a[i + 1] ? 1 + start[i + 1] : 1);
    }

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        //no change
        answer = max(answer, start[i]);

        int prv = endd[i - 1];
        int nxt = start[i + 1];

        answer = max(answer, 1 + prv);
        answer = max(answer, 1 + nxt);
        if (a[i + 1] - a[i - 1] > 1)
            answer = max(answer, prv + nxt + 1);
    }

    cout << answer << endl;
}
