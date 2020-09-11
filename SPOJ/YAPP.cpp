#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

LL fastExpo(LL base, LL p) {
    if (p == 0)
        return 1;

    LL half = fastExpo(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

int main() {
    int T, N;

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);
        printf("%lld\n", fastExpo(2, N - 1));
    }
}
