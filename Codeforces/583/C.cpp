#include<bits/stdc++.h>
using namespace std;

int n, balance, keep;
bool canFix, valid;
string s;

int main() {
    cin >> n >> s;

    balance = 0;
    canFix = true;
    valid = true;
    keep = -1;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(')
            balance += 1;
        else {
            if (balance > 0) {
                balance -= 1;
            } else {
                if (canFix) {
                    canFix = false;
                    keep = 1;
                } else {
                    valid = false;
                    break;
                }
            }
        }
    }

    if (!valid) {
        cout << "No\n";
    } else {
        if (keep == -1) {
            if (balance == 0)
                cout << "Yes\n";
            else
                cout << "No\n";
        } else {
            if (balance == 1)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }
}
