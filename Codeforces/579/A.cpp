#include<bits/stdc++.h>
using namespace std;
#define MAXN 200

int q, n, p[MAXN + 3];

int main() {
    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            p[i] -= 1;
        }

        bool canClockwise = true;
        for (int i = 1; i < n; i++) {
            if (p[i] != (p[i - 1] + 1)%n)
                canClockwise = false;
        }

        bool canAnticlockwise = true;
        for (int i = 1; i < n; i++) {
            if (p[i] != (p[i - 1] - 1 + n)%n)
                canAnticlockwise = false;
        }

        if (canClockwise || canAnticlockwise)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
