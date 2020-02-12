/*
* ai <= mi. This can be proven by using the fact that sequence 'a' is non-decreasing.
* Formulate each ai:
    a1 = a1
    a2 = 2*m1 - a1
    a3 = a1 - 2*m1 + 2*m2
    a4 = 2*m1 - 2*m2 + 2*m3 - a1
    and so on.

    Notice that each equation will yield either a new upper or lower bound for a1 (by combining the fact from previous observation). We take the minimal upper bound and maximal lower bound.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 5000000
#define INF 1e18

int N;
LL lowerbound, upperbound, sum;

int main() {
    scanf("%d", &N);

    lowerbound = -INF;
    upperbound = +INF;
    sum = 0;

    int prevM = 0;
    for (int i = 1; i <= N; i++) {
        int m;
        scanf("%d", &m);

        if (i % 2 == 0) {
            sum += 2 * prevM;
            lowerbound = max(lowerbound, sum - m);
        } else {
            sum -= 2 * prevM;
            upperbound = min(upperbound, sum + m);
        }

        prevM = m;
    }

    printf("%lld\n", max((LL) 0, upperbound - lowerbound + 1));
}
