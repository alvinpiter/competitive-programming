#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, t, d;
LL currentTime;

int main() {
    scanf("%d", &n);

    currentTime = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &t, &d);

        if (t >= currentTime) {
            currentTime = t + d;
        } else {
            currentTime += d;
        }
    }

    printf("%lld\n", currentTime);
}
