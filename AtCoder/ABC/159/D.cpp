#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int N, A[MAXN + 3], cnt[MAXN + 3];
LL allWays;

LL C2(int n) {
    return ((LL) n * n - n)/2;
}

int main() {
    cin >> N;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= N; i++) {
        cin >> A[i];

        cnt[A[i]] += 1;
    }

    allWays = 0;
    for (int i = 1; i <= MAXN; i++) allWays += C2(cnt[i]);

    for (int k = 1; k <= N; k++) {
        cout << allWays - C2(cnt[A[k]]) + C2(cnt[A[k]] - 1) << endl;
    }
}
