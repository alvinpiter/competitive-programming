#include<bits/stdc++.h>
using namespace std;

int t, n;
pair<int, int> packages[1003];

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> packages[i].first >> packages[i].second;

        sort(packages, packages + n);

        int currentX = 0;
        int currentY = 0;
        string answer = "";
        bool possible = true;

        for (int i = 0; i < n; i++) {
            int dx = packages[i].first - currentX;
            int dy = packages[i].second - currentY;

            if (dx < 0 || dy < 0) {
                possible = false;
                break;
            }

            for (int j = 1; j <= dx; j++)
                answer += "R";

            for (int j = 1; j <= dy; j++)
                answer += "U";

            currentX = packages[i].first;
            currentY = packages[i].second;
        }

        if (possible) {
            cout << "YES\n";
            cout << answer << endl;
        } else
            cout << "NO\n";
    }
}
