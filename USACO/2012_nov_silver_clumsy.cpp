#include<bits/stdc++.h>
using namespace std;

int main() {
    freopen("clumsy.in", "r", stdin);
    freopen("clumsy.out", "w", stdout);

    string S;
    int opens, answer;

    cin >> S;

    opens = 0;
    answer = 0;
    for (int i = 0; i < (int) S.length(); i++) {
        if (S[i] == '(')
            opens += 1;
        else {
            if (opens == 0) {
                //this ) must be toggled
                opens = 1;
                answer += 1;
            } else {
                opens -= 1;
            }
        }
    }

    cout << answer + opens/2 << endl;
}
