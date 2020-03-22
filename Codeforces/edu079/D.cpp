#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 998244353
#define MAXN 1000000
#define MAXA 1000000

LL fastExponentiation(LL base, LL p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;
    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

int N, counter[MAXA + 3]; //counter[i] -> how many kids wants gift i.
vector<int> a[MAXN + 3];

int main() {
    scanf("%d", &N);

    memset(counter, 0, sizeof(counter));
    for (int i = 1; i <= N; i++) {
        int k, g;
        scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            scanf("%d", &g);
            a[i].push_back(g);

            counter[g] += 1;
        }
    }

    LL result = 0;
    for (int i = 1; i <= N; i++) {
        int k = a[i].size();
        int sumCount = 0;
        for (int j = 0; j < k; j++)
            sumCount += counter[a[i][j]];

        LL numerator = sumCount%MOD;
        LL denominator = fastExponentiation(((LL) N * N * k)%MOD, MOD - 2);
        LL temp = (numerator * denominator)%MOD;

        result = (result + temp)%MOD;
    }

    printf("%lld\n", result);
}
