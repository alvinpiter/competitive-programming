#include<bits/stdc++.h>
using namespace std;

/*
WLOG, a and b is taken from the set and c is our choice.
WLOG, a < b

a + b > c -> c < a + b (in worst case scenario, we must choose the minimal of these)
a + c > b -> c > b - a (in worst case scenario, we must choose the maximal of these)
*/

int main() {
    int n, l[200003];

    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
        scanf("%d", &l[i]);

    sort(l, l + n);

    int maxiC = l[0] + l[1] - 1;
    int miniC = l[n - 1] - l[0] + 1;

    if (maxiC < miniC)
        printf("NO\n");
    else {
        printf("YES\n");
        printf("%d\n", miniC);
    }
}
