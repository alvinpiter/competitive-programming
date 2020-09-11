#include<bits/stdc++.h>
using namespace std;

int t, n, k, currentCharIndex;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> k;

        currentCharIndex = 0;
        for (int i = 0; i < n; i++) {
            char c = ('a' + currentCharIndex);

            cout << c;

            currentCharIndex = (currentCharIndex + 1)%k;
        }
        cout << endl;
    }
}
