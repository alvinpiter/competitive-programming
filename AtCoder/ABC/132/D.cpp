#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 2000
#define MOD 1000000007

int N, K;
LL C[MAXN + 3][MAXN + 3];

int main() {
    for (int n = 0; n <= MAXN; n++) C[n][0] = 1;
    for (int k = 1; k <= MAXN; k++) C[0][k] = 0;
    for (int n = 1; n <= MAXN; n++) {
        for (int k = 1; k <= MAXN; k++) {
            C[n][k] = (C[n - 1][k] + C[n - 1][k - 1])%MOD;
        }
    }

    cin >> N >> K;
    for (int i = 1; i <= K; i++) {
        LL first = C[K - 1][i - 1];
        LL second = C[N - K + 1][i];

        cout << (first * second)%MOD << endl;
    }
}
