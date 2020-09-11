#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, k, current, sum, firstB, secondB;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> k;

        current = 1;
        sum = 0;
        while (sum < k) {
            sum += current;
            current += 1;
        }

        if (sum == k) {
            current -= 1;

            firstB = n - current;
            secondB = firstB + 1;
        } else {
            current -= 1;

            firstB = n - current;
            secondB = n - (k - (sum - current)) + 1;
        }

        for (int i = 1; i <= n; i++) {
            if (i == firstB || i == secondB)
                cout << "b";
            else
                cout << "a";
        }
        cout << endl;
    }
}
