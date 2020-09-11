#include<bits/stdc++.h>
using namespace std;
#define MAXN 2000
#define MAXA 100000
#define MOD 1000000007

int C[MAXN + 3][MAXN + 3]; //C(n, k)
int counter[MAXA + 3]; //counter[i] -> How many numbers are divisible by i
int N, K, answer;

/*
How many subset of size sz whose gcd is g
f(sz, g) = C(numDivisibleByG, sz) - f(sz, 2 * g) - f(sz, 3 * g) - ...
*/
int f(int sz, int g) {
    int dp[MAXA  + 3];
    memset(dp, 0, sizeof(dp));

    int bound = (MAXA/g);

    for (int i = bound; i >= 1; i--) {
        dp[i] = (sz <= N ? C[counter[i * g]][sz] : 0);
        for (int j = 2 * i; j <= bound; j += i)
            dp[i] = (dp[i] - dp[j] + MOD)%MOD;
    }

    return dp[1];
}

int main() {
    //Inititialize C
    for (int n = 0; n <= MAXN; n++)
        C[n][0] = 1;

    for (int k = 1; k <= MAXN; k++)
        C[0][k] = 0;

    for (int n = 1; n <= MAXN; n++) {
        for (int k = 1; k <= MAXN; k++) {
            C[n][k] = (C[n - 1][k] + C[n - 1][k - 1])%MOD;
        }
    }

    cin >> N >> K;

    memset(counter, 0, sizeof(counter));
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;

        counter[a] += 1;
    }

    //Initialize counter
    for (int i = 1; i <= MAXA; i++) {
        for (int j = 2 * i; j <= MAXA; j += i)
            counter[i] += counter[j];
    }

    answer = 0;
    for (int s = 1; s <= K; s++) {
        if (K % s == 0)
            answer = (answer + f(s, K/s))%MOD;
    }

    cout << answer << endl;
}
