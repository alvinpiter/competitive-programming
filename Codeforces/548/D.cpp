#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXM 100000

/*
dp[g] -> expected number of steps to reach 1 if current gcd is g
dp[g] = 1 + sum(dp[gcd(g, i)] * 1/m)

Notice that gcd(g, i) are divisors of g. So we can convert the formula to be:
dp[g] = 1 + sum(dp[d] * cnt(g, d) * 1/m), where cnt(g, d) is number of number from 1 to m whose gcd with g equals d.

cnt(g, d) can be calculated with inclusion-exclusion principle
*/

vector<int> divisor[MAXM + 3], primeFactor[MAXM + 3];

LL fastExponentiation(LL base, int p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

//Find how many numbers between 1 and x that is coprime with y
int cntCoprime(int x, int y) {
    int numPrime = (int) primeFactor[y].size();
    int cntNotCoprime = 0;

    for (int mask = 1; mask < (1 << numPrime); mask++) {
        int cntOnBit = 0;
        int mul = 1;
        for (int i = 0; i < numPrime; i++) {
            if (mask & (1 << i)) {
                cntOnBit += 1;
                mul *= primeFactor[y][i];
            }
        }

        if (cntOnBit%2 == 1)
            cntNotCoprime += x/mul;
        else
            cntNotCoprime -= x/mul;
    }

    return x - cntNotCoprime;
}

/*
Find how many numbers between 1 to m whose gcd with g is d. d is divisor of g.

Assume one of the number is x. Then we have:
x = a * d
g = b * d

a and b must be coprime.
*/
int cntGcd(int m, int g, int d) {
    int b = g/d;
    return cntCoprime(m/d, b);
}

int main() {
    //Find prime factors of each number from 1 to MAXM
    for (int i = 2; i <= MAXM; i++) {
        int num = i;
        for (int p = 2; p * p <= num; p++) {
            if (num % p == 0) {
                primeFactor[i].push_back(p);
                while (num % p == 0)
                    num /= p;
            }
        }

        if (num != 1)
            primeFactor[i].push_back(num);
    }

    //Find proper divisors of each number from 1 to MAXM
    for (int d = 1; d <= MAXM; d++) {
        for (int num = 2 * d; num <= MAXM; num += d)
            divisor[num].push_back(d);
    }

    int m;
    LL dp[MAXM + 3];

    cin >> m;

    dp[1] = 0;
    for (int g = 2; g <= m; g++) {
        LL sumProper = 0;
        for (auto d: divisor[g]) {
            LL temp = dp[d];
            temp = (temp * cntGcd(m, g, d))%MOD;
            temp = (temp * fastExponentiation(m, MOD - 2))%MOD;

            sumProper = (sumProper + temp)%MOD;
        }

        dp[g] = (1 + sumProper)%MOD;
        dp[g] = (dp[g] * m)%MOD;
        dp[g] = (dp[g] * fastExponentiation(m - m/g, MOD - 2))%MOD; //not proper
    }

    LL answer = 1;
    for (int g = 1; g <= m; g++) {
        answer = (answer + (dp[g] * fastExponentiation(m, MOD - 2))%MOD)%MOD;
    }

    cout << answer << endl;
}
