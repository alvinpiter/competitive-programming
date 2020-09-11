#include<bits/stdc++.h>
using namespace std;

int t, a[3];

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        for (int i = 0; i < 3; i++)
            cin >> a[i];

        int answer = 0;

        sort(a, a + 3);
        for (int i = 0; i < 3; i++) {
            if (a[i] > 0) {
                a[i] -= 1;
                answer += 1;
            }
        }

        if (a[0] > 0 && a[2] > 0) {
            a[0] -= 1;
            a[2] -= 1;
            answer += 1;
        }

        if (a[1] > 0 && a[2] > 0) {
            a[1] -= 1;
            a[2] -= 1;
            answer += 1;
        }

        if (a[0] > 0 && a[1] > 0) {
            a[0] -= 1;
            a[1] -= 1;
            answer += 1;
        }

        if (a[0] > 0 && a[1] > 0 && a[2] > 0)
            answer += 1;

        cout << answer << endl;
    }
}
