#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    //incorrect tree
    if (n < 6) {
        printf("-1\n");
    } else {
        for (int i = 2; i <= 4; i++)
            printf("%d %d\n", 1, i);

        for (int i = 5; i <= n; i++)
            printf("%d %d\n", 3, i);
    }

    //correct tree
    for (int i = 1; i < n; i++)
        printf("%d %d\n", i , i + 1);
}
