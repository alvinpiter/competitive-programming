#include<bits/stdc++.h>
using namespace std;
#define MAXN 3000

int N, a[MAXN + 3], b[MAXN + 3], c[MAXN + 3], dp0[MAXN + 3], dp1[MAXN + 2];

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> a[i];

    for (int i = 1; i <= N; i++)
        cin >> b[i];

    for (int i = 1; i <= N; i++)
        cin >> c[i];

    dp0[1] = a[1];
    dp1[1] = b[1];
    for (int i = 2; i <= N; i++) {
        dp0[i] = max(a[i] + dp1[i - 1], b[i] + dp0[i - 1]);
        dp1[i] = max(b[i] + dp1[i - 1], c[i] + dp0[i - 1]);
    }

    cout << dp0[N] << endl;
}
