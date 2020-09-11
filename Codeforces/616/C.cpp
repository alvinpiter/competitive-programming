#include<bits/stdc++.h>
using namespace std;
#define MAXN 3500

int t, n, m, k, a[MAXN + 3];

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        int cntPersuaded = min(k, m - 1);
        int cntNotPersuaded = (m - 1) - cntPersuaded;

        int answer = 0;
        for (int cntFrontPersuaded = 0; cntFrontPersuaded <= cntPersuaded; cntFrontPersuaded++) {
            int worse = 1e9;
            for (int cntFrontNotPersuaded = 0; cntFrontNotPersuaded <= cntNotPersuaded; cntFrontNotPersuaded++) {
                int cntFront = cntFrontPersuaded + cntFrontNotPersuaded;
                int cntBack = (cntPersuaded + cntNotPersuaded) - cntFront;

                worse = min(worse, max(a[cntFront + 1], a[n - cntBack]));
            }

            answer = max(answer, worse);
        }

        cout << answer << endl;
    }
}
