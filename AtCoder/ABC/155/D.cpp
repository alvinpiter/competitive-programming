#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int N;
LL K, A[MAXN + 3];

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    sort(A + 1, A + N + 1);

    LL lo = -1e18, hi = 1e18, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        LL numBelowMid = 0;
        for (int i = 1; i <= N; i++) {
            if (A[i] > 0) {
                int l = i + 1, r = N, m;
                while (r >= l) {
                    m = (l + r)/2;
                    if (A[i] * A[m] <= mid)
                        l = m + 1;
                    else
                        r = m - 1;
                }

                numBelowMid += (r - i);
            } else if (A[i] < 0) {
                int l = i + 1, r = N, m;
                while (r >= l) {
                    m = (l + r)/2;
                    if (A[i] * A[m] > mid)
                        l = m + 1;
                    else
                        r = m - 1;
                }

                numBelowMid += (N - l + 1);
            } else if (A[i] == 0) {
                if (mid >= 0)
                    numBelowMid += (N - i);
            }
        }

        if (numBelowMid < K)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    cout << lo << endl;
}
