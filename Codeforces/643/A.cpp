#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int minDigit(LL num) {
    int result = 9;
    while (num > 0) {
        result = min(result, (int) (num%10));
        num /= 10;
    }

    return result;
}

int maxDigit(LL num) {
    int result = 0;
    while (num > 0) {
        result = max(result, (int) (num%10));
        num /= 10;
    }

    return result;
}

int main() {
    int t;
    LL a, K;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%lld%lld", &a, &K);
        for (LL i = 2; i <= K; i++) {
            LL prevA = a;

            a = a + minDigit(a) * maxDigit(a);

            if (a == prevA)
                break;
        }

        printf("%lld\n", a);
    }
}
