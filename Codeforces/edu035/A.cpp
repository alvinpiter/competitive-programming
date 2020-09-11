#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a[100003], mini, answer, lastMiniIdx;

    cin >> n;

    mini = 1e9;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mini = min(mini, a[i]);
    }

    lastMiniIdx = -1;
    answer = n;
    for (int i = 1; i <= n; i++) {
        if (a[i] == mini) {
            if (lastMiniIdx != -1)
                answer = min(answer, i - lastMiniIdx);

            lastMiniIdx = i;
        }
    }

    cout << answer << endl;
}
