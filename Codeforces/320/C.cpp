#include<bits/stdc++.h>
using namespace std;

int main() {
    int a, b;

    cin >> a >> b;
    if (a == b) {
        printf("%.10lf\n", (double) a);
    } else if (b > a) {
        printf("-1\n");
    } else {
        int lo = 0, hi = 1000000000, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            double x = (a + b)/(2 * (mid + 1) * 1.0);

            if (x >= b && (2 * mid + 1)*x <= a && a <= (2 * mid + 2)*x)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        printf("%.10lf\n", (a + b)/(2 * (hi + 1) * 1.0));
    }
}
