/*
Important observations:
* a + b - 2*(a ^ b) = a XOR b
* 4k XOR (4k + 1) XOR (4k + 2) XOR (4k + 3) = 0

*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int T, N;
LL L, R, M, prefixXor[MAXN + 3];

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> L >> R >> M;

        N = (int) (R - L + 1);

        prefixXor[0] = 0;
        for (int i = 1; i <= N; i++)
            prefixXor[i] = prefixXor[i - 1] ^ (L + i - 1);

        int maxi = 0;
        for (int i = 1; i <= min(5, N); i++) {
            for (int j = max(1, N - 5); j <= N; j++) {
                if (i <= j) {
                    LL cost = prefixXor[j] ^ prefixXor[i - 1];
                    if (cost <= M)
                        maxi = max(maxi, j - i + 1);
                }
            }
        }

        cout << "Case #" << cases << ": " << maxi << endl;
    }
}
