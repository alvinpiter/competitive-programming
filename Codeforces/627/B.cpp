#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, a[5003];
    bool exist;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];

        exist = false;
        for (int i = 0; i < n && !exist; i++) {
            for (int j = i + 2; j < n && !exist; j++) {
                if (a[i] == a[j])
                    exist = true;
            }
        }

        if (exist)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
