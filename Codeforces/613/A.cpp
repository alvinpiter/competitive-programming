#include<bits/stdc++.h>
using namespace std;

int n, countL, countR;
string s;

int main() {
    cin >> n >> s;

    countL = countR = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'L')
            countL += 1;
        else
            countR += 1;
    }

    cout << countL + countR + 1 << endl;
}
