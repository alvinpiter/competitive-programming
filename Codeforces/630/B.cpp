#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int t, n, a[MAXN + 3], color[MAXN + 3];

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        memset(color, -1, sizeof(color));

        int numColor = 0;
        for (int p = 0; p < 11; p++) {
            bool exist = false;
            for (int i = 1; i <= n; i++) {
                if (color[i] == -1 && a[i] % primes[p] == 0)
                    exist = true;
            }

            if (!exist) continue;

            numColor += 1;
            for (int i = 1; i <= n; i++) {
                if (color[i] == -1 && a[i] % primes[p] == 0)
                    color[i] = numColor;
            }
        }

        cout << numColor << endl;
        for (int i = 1; i <= n; i++)
            cout << color[i] << " ";
        cout << endl;
    }
}
