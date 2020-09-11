#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, x, a, sum;
LL answer;
map<LL, int> counter; //counter[x] -> how many prefixes has some equals to x

int getCount(LL num) {
    if (counter.find(num) == counter.end())
        return 0;
    else
        return counter[num];
}

void increaseCount(LL num) {
    if (counter.find(num) == counter.end())
        counter[num] = 1;
    else
        counter[num] += 1;
}

int main() {
    scanf("%d%d", &n, &x);

    sum = 0;
    answer = 0;
    increaseCount(0);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);

        sum += a;

        answer += getCount(sum - x);

        increaseCount(sum);
    }

    printf("%lld\n", answer);
}
