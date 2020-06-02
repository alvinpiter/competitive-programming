#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    int n, q;
    LL sumOdds, sumEvens; //sum of elements add odd and even position respectively

    scanf("%d", &n);

    sumOdds = sumEvens = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        if (i%2 == 1)
            sumOdds += a;
        else
            sumEvens += a;
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int l, r, v;
        scanf("%d%d%d", &l, &r, &v);

        int cnt = r - l + 1;
        int numEvens, numOdds;

        if (cnt%2 == 0) {
            numEvens = cnt/2;
        } else {
            numEvens = (l % 2 == 0 ? cnt/2 + 1 : cnt/2);
        }

        numOdds = cnt - numEvens;

        sumEvens += (LL) numEvens * v;
        sumOdds += (LL) numOdds * v;

        if (n%2 == 0)
            printf("%lld\n", sumEvens - sumOdds);
        else
            printf("%lld\n", sumOdds - sumEvens);
    }
}
