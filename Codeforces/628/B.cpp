#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n;
    set<int> numbers;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        numbers.clear();
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;

            numbers.insert(x);
        }

        cout << numbers.size() << endl;
    }
}
