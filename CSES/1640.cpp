#include<bits/stdc++.h>
using namespace std;

int n, x, a;
map<int, int> idxOf;

int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        if (idxOf.find(x - a) != idxOf.end()) {
            cout << idxOf[x - a] << " " << i << endl;
            return 0;
        }

        idxOf[a] = i;
    }

    cout << "IMPOSSIBLE\n";
}
