#include<bits/stdc++.h>
using namespace std;
#define MAXN 200

int N, colorOfChar[26], colorOfIndex[MAXN + 3];

int main() {
    cin >> N;

    memset(colorOfChar, -1, sizeof(colorOfChar));
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;

        int charIndex = (c - 'a');

        //Check if there a decreasing subsequence of length at least 3
        bool can = true;
        for (int j = charIndex + 1; j < 26; j++) {
            if (colorOfChar[j] == 1)
                can = false;
        }

        if (can) {
            //If there is larger element before current element, then we will color it 1
            bool largerExist = false;
            for (int j = charIndex + 1; j < 26; j++) {
                if (colorOfChar[j] == 0) {
                    largerExist = true;
                    break;
                }
            }

            colorOfIndex[i] = (largerExist ? 1 : 0);
            colorOfChar[charIndex] = max(colorOfChar[charIndex], colorOfIndex[i]);
        } else {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    for (int i = 1; i <= N; i++)
        cout << colorOfIndex[i];

    cout << endl;
}
