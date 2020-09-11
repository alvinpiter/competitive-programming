#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

int m, n;
LL C[1100][1100];

int main() {
    for (int n = 0; n < 1100; n++)
        C[n][0] = 1;

    for (int k = 1; k < 1100; k++)
        C[0][k] = 0;

    for (int n = 1; n < 1100; n++) {
        for (int k = 1; k < 1100; k++)
            C[n][k] = (C[n - 1][k] + C[n - 1][k - 1])%MOD;
    }

    cin >> n >> m;
    cout << C[2*m + n - 1][n - 1] << endl;
}
