#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m, diff, answer;

    cin >> n >> m;

    if (m % n != 0) {
        cout << -1 << endl;
        return 0;
    }

    diff = m/n;

    answer = 0;
    while (diff % 2 == 0) {
        diff /= 2;
        answer += 1;
    }

    while (diff % 3 == 0) {
        diff /= 3;
        answer += 1;
    }

    if (diff != 1)
        cout << -1 << endl;
    else
        cout << answer << endl;
}
