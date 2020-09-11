#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    int n, d[200003], r;
    LL sumL, sumR, answer;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &d[i]);

    answer = 0;
    sumL = sumR = 0;
    r = n + 1;
    for (int l = 1; l <= n; l++) {
        sumL += d[l];
        while (r > 1 && sumR + d[r - 1] <= sumL) {
            sumR += d[r - 1];
            r = r - 1;
        }

        if (l < r && sumL == sumR)
            answer = max(answer, sumL);
    }

    printf("%lld\n", answer);
}
