#include<bits/stdc++.h>
using namespace std;

string S;
int x, y;

int main() {
    cin >> S;

    x = y = 0;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == 'U')
            y += 1;
        else if (S[i] == 'R')
            x += 1;
        else if (S[i] == 'D')
            y -= 1;
        else if (S[i] == 'L')
            x -= 1;
    }

    cout << x << " " << y << endl;
}
