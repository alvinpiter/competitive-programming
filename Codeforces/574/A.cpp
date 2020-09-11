#include<bits/stdc++.h>
using namespace std;

int n, k, cnt[1003];
int quota, answer;

int main() {
    cin >> n >> k;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;

        cnt[a] += 1;
    }

    quota = n/2 + (n%2 == 1 ? 1 : 0);
    answer = 0;
    for (int i = 1; i <= k; i++) {
        int numPackage = cnt[i]/2;

        quota -= numPackage;
        answer += 2 * numPackage;
        cnt[i] -= 2 * numPackage;
    }

    for (int i = 1; i <= k; i++) {
        if (cnt[i] > 0 && quota > 0) {
            quota -= 1;
            answer += 1;
            cnt[i] -= 1;
        }
    }

    cout << answer << endl;
}
