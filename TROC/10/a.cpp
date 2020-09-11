#include<bits/stdc++.h>
using namespace std;

int main() {
    string S, T;

    cin >> S >> T;

    bool same = true;
    for (int i = 0; i < S.length(); i++) {
        if (tolower(S[i]) != tolower(T[i]))
            same = false;
    }

    if (same)
        cout << "20/20\n";
    else
        cout << "x_x\n";
}
