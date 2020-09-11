#include<bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c, d;

    cin >> a >> b >> c >> d;

    for (int turn = 0; ; turn = (turn + 1)%2) {
        if (turn == 0) {
            c -= b;
            if (c <= 0) {
                cout << "Yes\n";
                return 0;
            }
        } else {
            a -= d;
            if (a <= 0) {
                cout << "No\n";
                return 0;
            }
        }
    }
}
