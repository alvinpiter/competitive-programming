#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

int t, n, coins[1003][1003];

LL walk(int r, int c) {
    LL total = 0;

    while (r <= n && c <= n) {
        total += coins[r][c];
        r += 1;
        c += 1;
    }

    return total;
}

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> coins[i][j];
            }
        }

        LL answer = 0;
        for (int i = 1; i <= n; i++) {
            answer = max(answer, walk(i, 1));
        }

        for (int j = 1; j <= n; j++) {
            answer = max(answer, walk(1, j));
        }

        cout << "Case #" << cases << ": " << answer << endl;
    }
}
