#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n, p[MAXN + 3];
LL answer;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    sort(p, p + n);

    answer = 0;
    for (int i = 0; i < n; i++)
        answer += abs(p[i] - p[n/2]);

    printf("%lld\n", answer);
}
