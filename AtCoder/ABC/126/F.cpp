#include<bits/stdc++.h>
using namespace std;

int main() {
    int M, K;
    cin >> M >> K;

    if (K >= (1 << M)) {
        cout << -1 << endl;
        return 0;
    }

    if (M == 1) {
        if (K == 0)
            cout << 0 << " " << 0 << " " << 1 << " " << 1 << endl;

        if (K == 1)
            cout << -1 << endl;

        return 0;
    }

    vector<int> X;
    for (int i = 0; i < (1 << M); i++) {
        if (i != K) X.push_back(i);
    }

    for (int i = 0; i < X.size(); i++) cout << X[i] << " ";
    cout << K << " ";
    for (int i = X.size() - 1; i >= 0; i--) cout << X[i] << " ";
    cout << K << endl;
}
