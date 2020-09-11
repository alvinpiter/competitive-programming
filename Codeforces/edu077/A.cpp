#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, c, sum, answer;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c >> sum;

        answer = 0;
        for (int i = 1; i <= c; i++) {
            int s = sum/c + (i <= sum%c ? 1 : 0);
            answer += s * s;
        }

        cout << answer << endl;
    }
}
