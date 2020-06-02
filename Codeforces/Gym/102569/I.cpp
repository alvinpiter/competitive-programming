#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n;
vector<int> color[MAXN + 3];

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int val, col;
        scanf("%d%d", &val, &col);

        color[col].push_back(val);
    }

    bool possible = true;
    for (int col = 1; col <= MAXN; col++) {
        bool isSorted = true;
        for (int i = 1; i < (int) color[col].size(); i++) {
            if (color[col][i] < color[col][i - 1])
                isSorted = false;
        }

        possible = possible && isSorted;
    }

    if (possible)
        printf("YES\n");
    else
        printf("NO\n");
}
