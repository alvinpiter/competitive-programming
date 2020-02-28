#include<bits/stdc++.h>
using namespace std;

int q, n, a[103];

int main() {
    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        sort(a + 1, a + n + 1);

        bool exist = false;
        for (int i = 2; i <= n; i++) {
            if (a[i] - a[i - 1] == 1)
                exist = true;
        }

        if (exist)
            cout << "2\n";
        else
            cout << "1\n";
    }
}
