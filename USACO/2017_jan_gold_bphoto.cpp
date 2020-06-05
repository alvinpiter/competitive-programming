#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, A[MAXN + 3], L[MAXN + 3], R[MAXN + 3], bit[MAXN + 3];
vector<int> uniq;

void update(int idx, int val) {
    while (idx <= MAXN) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int main() {
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);

    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        uniq.push_back(A[i]);
    }

    sort(uniq.begin(), uniq.end());
    uniq.resize(distance(uniq.begin(), unique(uniq.begin(), uniq.end())));

    for (int i = 1; i <= N; i++)
        A[i] = (lower_bound(uniq.begin(), uniq.end(), A[i]) - uniq.begin()) + 1;

    memset(bit, 0, sizeof(bit));
    for (int i = 1; i <= N; i++) {
        L[i] = query(MAXN) - query(A[i]);
        update(A[i], 1);
    }

    memset(bit, 0, sizeof(bit));
    for (int i = N; i >= 1; i--) {
        R[i] = query(MAXN) - query(A[i]);
        update(A[i], 1);
    }

    int answer = 0;
    for (int i = 1; i <= N; i++) {
        if (max(L[i], R[i]) > 2 * min(L[i], R[i]))
            answer += 1;
    }

    printf("%d\n", answer);
}
