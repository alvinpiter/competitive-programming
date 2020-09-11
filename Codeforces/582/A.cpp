#include<bits/stdc++.h>
using namespace std;

int n, countOdd, countEven;

int main() {
    cin >> n;

    countOdd = countEven = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        if (x%2 == 0)
            countEven += 1;
        else
            countOdd += 1;
    }

    cout << min(countOdd, countEven) << endl;
}
