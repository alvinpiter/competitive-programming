#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, b, p, f, h, c;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> b >> p >> f >> h >> c;

        int answer = 0;
        for (int numBeef = 0; numBeef <= p; numBeef++) {
            for (int numChick = 0; numChick <= f; numChick++) {
                if (2 * numBeef + 2 * numChick <= b)
                    answer = max(answer, numBeef * h + numChick * c);
            }
        }

        cout << answer << endl;
    }
}
