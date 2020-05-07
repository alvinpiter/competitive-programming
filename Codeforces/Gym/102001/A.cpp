#include<bits/stdc++.h>
using namespace std;

int main() {
    string S;
    int cnt0, cnt1;

    cin >> S;

    cnt0 = cnt1 = 0;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == '0')
            cnt0 += 1;
        else
            cnt1 += 1;
    }

    if (cnt0 < cnt1) {
        for (int i = 0; i < S.length(); i++)
            cout << 0;
        cout << endl;
    } else if (cnt0 > cnt1) {
        for (int i = 0; i < S.length(); i++)
            cout << 1;
        cout << endl;
    } else {
        if (S[0] == '0') {
            cout << 1;
            for (int i = 0; i < S.length() - 1; i++)
                cout << 0;
            cout << endl;
        } else {
            cout << 0;
            for (int i = 0; i < S.length() - 1; i++)
                cout << 1;
            cout << endl;
        }
    }
}
