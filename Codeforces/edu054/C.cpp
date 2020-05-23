#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, d;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &d);

        int det = d * d - 4 * d;

        if (det < 0) {
            printf("N\n");
            continue;
        }

        double b = (d + sqrt(det))/2;
        if (b < 0 | d - b < 0) {
            printf("N\n");
            continue;
        }

        printf("Y %.10lf %.10lf\n", d - b, b);
    }
}
