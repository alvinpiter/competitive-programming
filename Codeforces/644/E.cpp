#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n;
    char grid[53][53];

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                cin >> grid[i][j];
        }

        bool valid = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (grid[i][j] == '1') {
                    bool isFloating = true;

                    if (i == n || grid[i + 1][j] == '1')
                        isFloating = false;

                    if (j == n || grid[i][j + 1] == '1')
                        isFloating = false;

                    if (isFloating)
                        valid = false;
                }
            }
        }

        if (valid)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
