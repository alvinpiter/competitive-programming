#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, color[3];

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> color[0] >> color[1] >> color[2];

        sort(color, color + 3);

        if (color[0] + color[1] < color[2] - 1)
            cout << "No\n";
        else
            cout << "Yes\n";
    }
}
