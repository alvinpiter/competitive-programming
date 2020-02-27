
#include<bits/stdc++.h>
using namespace std;

int T, N, A, numOdd, numEven;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        numOdd = numEven = 0;
        for (int i = 1; i <= N; i++) {
            cin >> A;

            if (A%2 == 0)
                numEven += 1;
            else
                numOdd += 1;
        }

        if (numEven == N)
            cout << "NO\n";
        else if (numOdd == N) {
            if (N%2 == 1)
                cout << "YES\n";
            else
                cout << "NO\n";
        } else
            cout << "YES\n";
    }
}
