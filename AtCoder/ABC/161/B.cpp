#include<bits/stdc++.h>
using namespace std;

int main() {
    int M, N, A[103], total, cnt;

    cin >> N >> M;

    total = 0;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        total += A[i];
    }

    cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (A[i] * 4 * M >= total)
            cnt += 1;
    }

    if (cnt >= M)
        cout << "Yes\n";
    else
        cout << "No\n";
}
