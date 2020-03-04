#include<bits/stdc++.h>
using namespace std;

string s;
vector<int> posOpen, posClose;

int main() {
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(')
            posOpen.push_back(i);
        else
            posClose.push_back(i);
    }

    int ptrOpen = 0;
    int ptrClose = posClose.size() - 1;
    while (ptrOpen < posOpen.size() && ptrClose >= 0 && posOpen[ptrOpen] < posClose[ptrClose]) {
        ptrOpen += 1;
        ptrClose -= 1;
    }

    vector<int> answer;
    for (int i = 0; i < ptrOpen; i++)
        answer.push_back(posOpen[i]);

    for (int i = ptrClose + 1; i < posClose.size(); i++)
        answer.push_back(posClose[i]);

    if (answer.size() > 0) {
        cout << "1\n";
        cout << answer.size() << endl;
        for (int i = 0; i < answer.size(); i++)
            cout << answer[i] + 1 << " ";
        cout << endl;
    } else
        cout << "0\n";
}
