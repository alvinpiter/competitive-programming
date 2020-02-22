#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int T;
LL N, answer;

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%lld", &N);

        LL a = N;
        LL b = N + 1;

        if (a % 2 == 0)
            answer = (a/2) * b;
        else
            answer = a * (b/2);

        printf("Case #%d: %lld\n", cases, answer);
    }
}
