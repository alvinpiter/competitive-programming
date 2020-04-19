#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    LL n, current, answer;

    cin >> n;

    if (n%2 == 1) {
        cout << 0 << endl;
    } else {
        n /= 2;

        current = 5;
        answer = 0;

        while (n/current > 0) {
            answer += n/current;
            current *= 5;
        }

        cout << answer << endl;
    }
}
