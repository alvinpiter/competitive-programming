#include<bits/stdc++.h>
using namespace std;
#define MAXN 100

int main() {
    int n, a[MAXN + 3], b[MAXN + 3];
    bool isOn[MAXN + 3];

    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;

        isOn[i] = (c == '1');
    }

    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];

    int answer = 0;
    for (int t = 0; t <= 10000; t++) {
        //toggle if possible
        for (int i = 1; i <= n; i++) {
            if (t >= b[i] && (t - b[i])%a[i] == 0)
                isOn[i] = !isOn[i];
        }

        int cntOn = 0;
        for (int i = 1; i <= n; i++) {
            if (isOn[i])
                cntOn += 1;
        }

        answer = max(answer, cntOn);
    }

    cout << answer << endl;
}
