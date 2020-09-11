#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int N, Q, A[MAXN + 3], SZ;
LL prefixSum[MAXN + 3];

int normalize(int x) {
    return SZ - x + 1;
}

void update(int v) {
    SZ += 1;
    prefixSum[SZ] = prefixSum[SZ - 1] + v;
}

LL query(int x, int y) {
    return prefixSum[normalize(x)] - prefixSum[normalize(y) - 1];
}

int main() {
    cin >> N;
    for (int i = N; i >= 1; i--)
        cin >> A[i];

    cin >> Q;

    prefixSum[0] = 0;
    for (int i = 1; i <= N; i++)
        prefixSum[i] = prefixSum[i - 1] + A[i];

    SZ = N;
    for (int i = 1; i <= Q; i++) {
        int t, l, r, x;

        cin >> t;
        if (t == 1) {
            cin >> l >> r;

            cout << query(l, r) << endl;
        } else {
            cin >> x;

            update(x);
        }
    }
}
