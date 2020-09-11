#include<bits/stdc++.h>
using namespace std;

int main() {
    int T, N, a, last;
    bool valid;

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        last = -1;
        valid = true;
        for (int i = 1; i <= N; i++) {
            cin >> a;
            if (a == 1) {
                if (last != -1 && i - last < 6)
                    valid = false;

                last = i;
            }
        }

        if (valid)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
