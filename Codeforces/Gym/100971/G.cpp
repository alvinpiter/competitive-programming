#include<bits/stdc++.h>
using namespace std;

int main() {
    int a, b, sz[2][2];

    scanf("%d%d", &a, &b);
    scanf("%d%d", &sz[0][0], &sz[0][1]);
    scanf("%d%d", &sz[1][0], &sz[1][1]);

    bool possible = false;
    for (int firstWidthIdx = 0; firstWidthIdx < 2; firstWidthIdx++) {
        for (int secondWidthIdx = 0; secondWidthIdx < 2; secondWidthIdx++) {
            int w1 = sz[0][firstWidthIdx];
            int h1 = sz[0][1 - firstWidthIdx];
            int w2 = sz[1][secondWidthIdx];
            int h2 = sz[1][1 - secondWidthIdx];

            if (max(w1, w2) <= a && h1 + h2 <= b)
                possible = true;

            if (max(h1, h2) <= b && w1 + w2 <= a)
                possible = true;
        }
    }

    if (possible)
        printf("YES\n");
    else
        printf("NO\n");
}
