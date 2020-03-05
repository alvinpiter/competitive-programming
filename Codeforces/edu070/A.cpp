#include<bits/stdc++.h>
using namespace std;

int t;
string x, y;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> x >> y;

        int lsbY;
        for (int i = y.length(); i >= 0; i--) {
            if (y[i] == '1') {
                lsbY = y.length() - i;
                break;
            }
        }

        int lsbX;
        for (int i = x.length(); i >= 0; i--) {
            if (x[i] == '1' && x.length() - i >= lsbY) {
                lsbX = x.length() - i;
                break;
            }
        }

        cout << lsbX - lsbY << endl;
    }
}
