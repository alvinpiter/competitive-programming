#include<bits/stdc++.h>
using namespace std;

int N, M, Q, a[55], b[55], c[55], d[55], A[12];
int maxScore;

void generate(int idx) {
    if (idx == N + 1) {
        int score = 0;
        for (int i = 1; i <= Q; i++) {
            if (A[b[i]] - A[a[i]] == c[i])
                score += d[i];
        }

        maxScore = max(maxScore, score);
        return;
    }

    for (int num = A[idx - 1]; num <= M; num++) {
        A[idx] = num;
        generate(idx + 1);
    }
}

int main() {
    cin >> N >> M >> Q;
    for (int i = 1; i <= Q; i++)
        cin >> a[i] >> b[i] >> c[i] >> d[i];

    maxScore = 0;

    A[0] = 1;
    generate(1);

    cout << maxScore << endl;
}
