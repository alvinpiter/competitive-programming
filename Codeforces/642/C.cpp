#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    int t, n;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);

        LL answer = 0;
        int len = 1, distance = 0;

        for (int rep = 1; rep <= (n + 1)/2; rep++) {
            int cnt = 4 * len - 4;
            answer += (LL) distance * cnt;

            len += 2;
            distance += 1;
        }

        printf("%lld\n", answer);
    }
}
