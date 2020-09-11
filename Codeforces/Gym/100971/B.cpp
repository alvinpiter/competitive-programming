#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<int> fixed;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;

        if (p == i)
            fixed.push_back(i);
    }

    if (fixed.size() == 0) {
        cout << 0 << endl;
    } else if (fixed.size() == 1) {
        cout << 1 << endl;
        cout << fixed[0] << " " << (fixed[0] == 1 ? 2 : 1) << endl;
    } else if (fixed.size() % 2 == 0) {
        cout << (int) fixed.size()/2 << endl;
        for (int i = 0; i < (int) fixed.size(); i += 2)
            cout << fixed[i] << " " << fixed[i + 1] << endl;
    } else if (fixed.size() % 2 == 1) {
        cout << (int) fixed.size()/2 + 1 << endl;
        cout << fixed[0] << " " << fixed[1] << endl;
        for (int i = 1; i < (int) fixed.size(); i += 2)
            cout << fixed[i] << " " << fixed[i + 1] << endl;
    }
}
