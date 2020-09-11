#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    int t;
    LL n, k, answer;

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> k;

        answer = 0;
        while (n > 0) {
            if (n%k == 0) {
                answer += 1;
                n /= k;
            } else {
                answer += n%k;
                n -= n%k;
            }
        }

        cout << answer << endl;
    }
}
