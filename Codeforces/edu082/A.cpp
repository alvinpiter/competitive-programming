#include<bits/stdc++.h>
using namespace std;

int main() {
    int T;
    string s;

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> s;

        int answer = s.length();
        int numOne = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '1')
                numOne += 1;
        }

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '1') break;
            answer -= 1;
        }

        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '1') break;
            answer -= 1;
        }

        answer -= numOne;

        cout << max(answer, 0) << endl;
    }
}
