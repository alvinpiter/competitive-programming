#include<bits/stdc++.h>
using namespace std;

int main() {
    int q, answer;
    long long int n;

    cin >> q;
    for (int cases = 1; cases <= q; cases++) {
        cin >> n;

        answer = 0;
        while (n != 1) {
            if (n % 2 == 0) {
                n /= 2;
                answer += 1;
            } else if (n % 3 == 0) {
                n = (n/3) * 2;
                answer += 1;
            } else if (n % 5 == 0) {
                n = (n/5) * 4;
                answer += 1;
            } else
                break;
        }

        if (n != 1)
            cout << -1 << endl;
        else
            cout << answer << endl;
    }
}
