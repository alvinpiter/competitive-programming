#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, k, answer;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> k;

        answer = n;
        for (int i = 1; i * i <= n; i++) {
            if (n%i == 0) {
                if (i <= k)
                    answer = min(answer, n/i);

                if (n/i <= k)
                    answer = min(answer, i);
            }
        }

        cout << answer << endl;
    }
}
