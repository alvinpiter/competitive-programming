#include<bits/stdc++.h>
using namespace std;

void print1(int rep) {
    for (int i = 1; i <= rep; i++)
        cout << 1 << " ";
}

int main() {
    int n, m, a[503][503], currentXor;

    currentXor = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (j == 1)
                currentXor ^= a[i][j];
        }
    }

    if (currentXor > 0) {
        cout << "TAK\n";
        print1(n);
        cout << endl;

        return 0;
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = 2; j <= m; j++) {
                if (a[i][j] != a[i][1]) {
                    cout << "TAK\n";
                    print1(i - 1);
                    cout << j << " ";
                    print1(n - i);
                    cout << endl;

                    return 0;
                }
            }
        }

        cout << "NIE\n";
    }
}
