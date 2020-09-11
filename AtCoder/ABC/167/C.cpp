#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, M, X, C[13], A[13][13], answer;

    cin >> N >> M >> X;
    for (int i = 0; i < N; i++) {
        cin >> C[i];
        for (int j = 0; j < M; j++)
            cin >> A[i][j];
    }

    answer = 1e9;
    for (int mask = 0; mask < (1 << N); mask++) {
        int cnt[13], cost = 0;
        memset(cnt, 0, sizeof(cnt));

        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                cost += C[i];
                for (int j = 0; j < M; j++) {
                    cnt[j] += A[i][j];
                }
            }
        }

        bool valid = true;
        for (int j = 0; j < M; j++) {
            if (cnt[j] < X)
                valid = false;
        }

        if (valid)
            answer = min(answer, cost);
    }

    if (answer < 1e9)
        cout << answer << endl;
    else
        cout << -1 << endl;
}
