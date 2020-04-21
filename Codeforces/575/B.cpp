#include<bits/stdc++.h>
using namespace std;

int main() {
    int q, n, k;
    vector<int> posOdd;

    scanf("%d", &q);
    for (int cases = 1; cases <= q; cases++) {
        scanf("%d%d", &n, &k);

        posOdd.clear();
        for (int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);

            if (a%2 == 1)
                posOdd.push_back(i);
        }

        int numOdd = (int) posOdd.size();
        if (numOdd < k || (numOdd - (k - 1))%2 == 0)
            printf("NO\n");
        else {
            printf("YES\n");
            for (int i = 0; i < k - 1; i++)
                printf("%d ", posOdd[i]);

            printf("%d\n", n);
        }
    }
}
