#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define LL long long int
#define MAXN 200000

LL factorial[MAXN + 3];

LL fastExponentiation(LL base, LL p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p % 2 == 0) return halfhalf;
    if (p % 2 == 1) return (halfhalf * base)%MOD;
}

LL C(int n, int k) {
    if (k > n) return 0;

    LL numerator = factorial[n];
    LL denominator = (factorial[n - k] * factorial[k])%MOD;
    return (numerator * fastExponentiation(denominator, MOD - 2))%MOD;
}

int main() {
    factorial[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        factorial[i] = (factorial[i - 1] * i)%MOD;
    }

    int N, M, K;

    cin >> N >> M >> K;

    LL answer, sumHorizontal = 0, sumVertical = 0;

    //sum horizontal distances
    for (int dist = 1; dist < M; dist++) {
        LL temp = 1;

        temp = (temp * (M - dist))%MOD; //There are (M - dist) ways to choose the first two place with distance dist
        temp = (temp * N * N)%MOD; //Number of ways to choose the rows of the first two place
        temp = (temp * C(N * M - 2, K - 2))%MOD; //Spread K - 2 leftovers into other cells
        temp = (temp * dist)%MOD; //Each of them contributes dist to answer

        sumHorizontal = (sumHorizontal + temp)%MOD;
    }

    //sum vertical distances (similar to the previous)
    for (int dist = 1; dist < N; dist++) {
        LL temp = 1;

        temp = (temp * (N - dist))%MOD;
        temp = (temp * M * M)%MOD;
        temp = (temp * C(N * M - 2, K - 2))%MOD;
        temp = (temp * dist)%MOD;

        sumVertical = (sumVertical + temp)%MOD;
    }

    answer = (sumHorizontal + sumVertical)%MOD;

    cout << answer << endl;
}
