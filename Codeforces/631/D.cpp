#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    int t, d, m;
    LL answer;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> d >> m;

        answer = 1;
        for (int bit = 0; bit <= 30; bit++) {
            if ((1 << bit) > d)
                break;

            int upperbound = min(d + 1, (1 << (bit + 1)));
            int lowerbound = (1 << bit);
            int num = (upperbound - lowerbound);

            answer = (answer * (num + 1))%m;
        }

        answer = (answer - 1 + m)%m;

        cout << answer << endl;
    }
}
