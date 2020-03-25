#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, f[10];
    string s;

    cin >> n >> s;
    for (int i = 1; i <= 9; i++)
        cin >> f[i];

    int idx;
    for (idx = 0; idx < s.length(); idx++) {
        int currentNumber = s[idx] - '0';
        if (f[currentNumber] > currentNumber)
            break;
    }

    if (idx < s.length()) {
        for (int i = idx; i < s.length(); i++) {
            int currentNumber = s[i] - '0';
            int newNumber = f[currentNumber];

            if (currentNumber <= newNumber)
                s[i] = (newNumber + '0');
            else
                break;
        }
    }

    cout << s << endl;
}
