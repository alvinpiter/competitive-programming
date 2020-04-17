#include<bits/stdc++.h>
using namespace std;

/*
absorp then lightning -> x/2 + 10 - 10 -> x/2
lightning then absorp -> (x - 10)/2 + 10 -> x/2 + 5
*/
int main() {
    int t, x, n, m, answer;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> x >> n >> m;

        answer = 0;
        while (true) {
            if (n == 0)
                break;

            int nxt = x/2 + 10;

            if (nxt > x)
                break;
            else {
                n -= 1;
                x = nxt;
            }
        }

        if (10 * m >= x)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
