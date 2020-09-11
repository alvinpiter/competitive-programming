#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, cnt[200003];

    cin >> n;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;

        cnt[a] += 1;
    }

    int sum = 0;
    for (int i = 1; i <= 200000; i++)
        sum += cnt[i]/2;

    cout << sum/2 << endl;
}
