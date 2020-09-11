#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int main() {
    int N, A[MAXN + 3], F[MAXN + 3];
    LL K;

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> A[i];
    for (int i = 1; i <= N; i++)
        cin >> F[i];

    sort(A + 1, A + N + 1);
    sort(F + 1, F + N + 1, greater<int>());

    LL lo = 0, hi = 1e18 + 10, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        LL need = 0;
        for (int i = 1; i <= N; i++)
            need += max((LL) 0, A[i] - mid/F[i]);

        if (need <= K)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    cout << lo << endl;
}
