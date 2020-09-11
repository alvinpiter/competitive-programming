#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int T, N, K;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> K;
        if ((N + K)%2 != 0) {
            cout << "NO\n";
            continue;
        }

        LL sum = ((LL) K * K + K)/2;
        if (N + K >= 2 * sum)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
