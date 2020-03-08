#include<bits/stdc++.h>
using namespace std;

int t, n;
vector<int> odd, even;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        odd.clear();
        even.clear();
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;

            if (a%2 == 1)
                odd.push_back(i);
            else
                even.push_back(i);
        }

        if (even.size() > 0) {
            cout << 1 << endl;
            cout << even[0] << endl;
        } else {
            if (odd.size() >= 2) {
                cout << 2 << endl;
                cout << odd[0] << " " << odd[1] << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }
}
