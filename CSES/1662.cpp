#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

//countMod[i] = how many prefixes whose sum modolo n equals to i
int n, a, sum, countMod[MAXN + 3];
LL answer;

//Return the remainder when number is divided by m
//number might be negative
int mod(int number, int m) {
    if (number >= 0) {
        return number%m;
    } else {
        return (abs(number)/m + (abs(number)%m == 0 ? 0 : 1))*m + number;
    }
}

int main() {
    scanf("%d", &n);

    sum = answer = 0;
    countMod[0] = 1;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);

        sum = mod(sum + a, n);

        answer += countMod[sum];

        countMod[sum] += 1;
    }

    printf("%lld\n", answer);
}
