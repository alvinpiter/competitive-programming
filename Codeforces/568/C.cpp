#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXT 100

int n, M, t[MAXN + 3], counterT[MAXT + 3];

int main() {
    cin >> n >> M;
    for (int i = 1; i <= n; i++)
        cin >> t[i];

    memset(counterT, 0, sizeof(counterT));

    int prefixSum = 0;
    for (int i = 1; i <= n; i++) {
        int totalRemove = max(0, prefixSum + t[i] - M);

        int countRemove = 0;
        for (int j = MAXT; j >= 1; j--) {
            if (counterT[j] == 0) continue;

            if (totalRemove > j * counterT[j]) {
                countRemove += counterT[j];
                totalRemove -= j * counterT[j];
            } else {
                countRemove += (totalRemove/j + (totalRemove%j == 0 ? 0 : 1));
                totalRemove = 0;
                break;
            }
        }

        counterT[t[i]] += 1;
        prefixSum += t[i];

        if (i > 1)
            cout << " ";

        cout << countRemove;
    }
    cout << endl;
}
