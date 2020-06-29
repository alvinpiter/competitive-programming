#include<bits/stdc++.h>
using namespace std;
#define MAXT 5000000

int T, A, B, closest[MAXT + 3];
bool canReach[MAXT + 3];

int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    cin >> T >> A >> B;

    canReach[0] = true;
    for (int i = 1; i <= T; i++) {
        canReach[i] = false;

        if (i >= A)
            canReach[i] = (canReach[i] || canReach[i - A]);

        if (i >= B)
            canReach[i] = (canReach[i] || canReach[i - B]);
    }

    closest[0] = 0;
    int last = 0;
    for (int i = 1; i <= T; i++) {
        if (canReach[i])
            last = i;

        closest[i] = last;
    }

    int maxi = 0;
    for (int i = 1; i <= T; i++) {
        if (canReach[i]) {
            maxi = max(maxi, i);
            maxi = max(maxi, i/2 + closest[T - i/2]);
        }
    }

    cout << maxi << endl;
}
