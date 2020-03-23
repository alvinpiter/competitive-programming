#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, x, y, sumX, sumY;

    cin >> n;

    sumX = 0;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        sumX += x;
    }

    sumY = 0;
    for (int i = 1; i <= n; i++) {
        cin >> y;
        sumY += y;
    }

    if (sumX >= sumY)
        cout << "Yes\n";
    else
        cout << "No\n";
}
