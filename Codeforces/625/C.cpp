#include<bits/stdc++.h>
using namespace std;

int n;
string s;

int main() {
    cin >> n >> s;

    for (char c = 'z'; c >= 'a'; ) {
        int idxToRemove = -1;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == c) {
                if (i > 0 && s[i - 1] == c - 1) {
                    idxToRemove = i;
                    break;
                }

                if (i < s.length() - 1 && s[i + 1] == c - 1) {
                    idxToRemove = i;
                    break;
                }
            }
        }

        if (idxToRemove == -1)
            c--;
        else {
            s = s.substr(0, idxToRemove) + s.substr(idxToRemove + 1);
        }
    }

    cout << n - s.length() << endl;
}
