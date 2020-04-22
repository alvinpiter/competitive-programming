#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, balance, color[200003];

    cin >> n;

    balance = 0;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;

        if (c == '(') {
            balance += 1;
            color[i] = balance%2;
        } else {
            color[i] = balance%2;
            balance -= 1;
        }
    }

    for (int i = 1; i <= n; i++)
        cout << color[i];
    cout << endl;
}
