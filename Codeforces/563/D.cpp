#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    vector<int> prefixXOR;

    cin >> n >> x;

    prefixXOR.push_back(0);
    for (int i = 1; i < (1 << n); i++) {
        if ((x^i) < i)
            continue;
        else
            prefixXOR.push_back(i);
    }

    cout << prefixXOR.size() - 1 << endl;
    if (prefixXOR.size() - 1 > 0) {
        for (int i = 0; i < prefixXOR.size() - 1; i++)
            cout << (prefixXOR[i] ^ prefixXOR[i + 1]) << " ";
        cout << endl;
    }
}
