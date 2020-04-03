#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, a[MAXN + 3];
double prefix[MAXN + 3];

pair<double, double> getWeakness(double x) {
    prefix[0] = 0;
    for (int i = 1; i <= N; i++)
        prefix[i] = prefix[i - 1] + (a[i] - x);

    double minPrefix = 0, maxPrefix = 0;

    double maxF = -1e10, maxG = -1e10;
    for (int j = 1; j <= N; j++) {
        double F = prefix[j] - minPrefix;
        double G = -prefix[j] + maxPrefix;

        maxF = max(maxF, F);
        maxG = max(maxG, G);

        minPrefix = min(minPrefix, prefix[j]);
        maxPrefix = max(maxPrefix, prefix[j]);
    }

    return {maxF, maxG};
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);

    double lo = -10000, hi = 10000, mid;
    for (int rep = 1; rep <= 100; rep++) {
        mid = (lo + hi)/2.0;

        auto weakness = getWeakness(mid);

        if (weakness.first > weakness.second)
            lo = mid;
        else
            hi = mid;
    }

    auto weakness = getWeakness(lo);

    printf("%.10lf\n", max(weakness.first, weakness.second));
}
