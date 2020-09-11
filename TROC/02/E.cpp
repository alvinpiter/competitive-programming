#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 2000

LL factorial[MAXN + 3], C[MAXN + 3][MAXN + 3], answer;
int N, A[MAXN + 3], g[MAXN + 3]; //g[i] = How many people from village i exchange gifts with people from village i + 1

int main() {
    factorial[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        factorial[i] = (factorial[i - 1] * i)%MOD;

    for (int i = 0; i <= MAXN; i++)
        C[i][0] = 1;

    for (int j = 1; j <= MAXN; j++)
        C[0][j] = 0;

    for (int i = 1; i <= MAXN; i++) {
        for (int j = 1; j <= MAXN; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1])%MOD;
    }

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    if (N == 2) {
        if (A[1] != A[2])
            cout << "0\n";
        else
            cout << factorial[A[1]] << endl;

        return 0;
    }

    answer = 0;
    for (int _g = 0; _g <= A[1]; _g++) {
        g[1] = _g;
        for (int i = 2; i <= N; i++)
            g[i] = A[i] - g[i - 1];

        bool valid = true; //Valid is when all g[i] are non negative and g[1] + g[N] = A[1]
        for (int i = 1; i <= N; i++) {
            if (g[i] < 0)
                valid = false;
        }

        if (g[1] + g[N] != A[1])
            valid = false;

        if (valid) {
            LL numWays = 1;
            for (int i = 1; i <= N; i++) {
                numWays = (numWays * C[A[i]][g[i]])%MOD;
                numWays = (numWays * factorial[g[i]])%MOD;
            }

            answer = (answer + numWays)%MOD;
        }
    }

    cout << answer << endl;
}
