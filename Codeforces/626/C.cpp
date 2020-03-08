#include<bits/stdc++.h>
using namespace std;

int n, firstWrongIndex, balance, answer;
string s;

int main() {
    cin >> n;
    cin >> s;

    firstWrongIndex = -1;
    balance = 0;
    answer = 0;
    for (int i = 0; i < s.length(); i++) {
        balance += (s[i] == '(' ? 1 : -1);

        if (balance < 0) {
            if (firstWrongIndex == -1) {
                firstWrongIndex = i;
            }
        } else if (balance == 0) {
            if (firstWrongIndex != -1) {
                answer += (i - firstWrongIndex + 1);
                firstWrongIndex = -1;
            }
        }
    }

    if (balance == 0 && firstWrongIndex == -1)
        cout << answer << endl;
    else
        cout << -1 << endl;
}
