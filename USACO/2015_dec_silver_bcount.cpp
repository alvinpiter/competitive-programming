#include<bits/stdc++.h>
using namespace std;

int main() {
    freopen("bcount.in", "r", stdin);
    freopen("bcount.out", "w", stdout);

    int N, Q, psum[3][100003];

    cin >> N >> Q;

    memset(psum, 0, sizeof(psum));
    for (int i = 1; i <= N; i++) {
        int t;
        cin >> t;

        psum[t - 1][i] = 1;
    }

    for (int t = 0; t < 3; t++) {
        for (int i = 1; i <= N; i++)
            psum[t][i] += psum[t][i - 1];
    }

    for (int i = 1; i <= Q; i++) {
        int l, r;
        cin >> l >> r;

        for (int t = 0; t < 3; t++) {
            cout << psum[t][r] - psum[t][l - 1];
            if (t == 2)
                cout << endl;
            else
                cout << " ";
        }
    }
}
