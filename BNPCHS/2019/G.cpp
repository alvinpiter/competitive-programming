#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int T, N, M, carry;
LL answer;

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &M);

        answer = 0;
        carry = 0;
        for (int i = 1; i <= N; i++) {
            int X, need;
            scanf("%d", &X);

            need = M - X;

            if (need > carry) {
                answer += (need - carry);
                carry = need;
            } else
                carry = min(carry, need);
        }

        printf("Case #%d: %lld\n", cases, answer);
    }
}
