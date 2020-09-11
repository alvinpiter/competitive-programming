#include<bits/stdc++.h>
using namespace std;

int T, r, R;

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &r, &R);

        double total = (double) r + R + sqrt(pow(R + r, 2) - pow((2*r*sqrt(3))/3, 2));
        printf("Case #%d: %.5f\n", cases, total);
    }
}
