#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int firstBracket, lastBracket, firstColon, lastColon;

    cin >> s;

    firstBracket = -1;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '[') {
            firstBracket = i;
            break;
        }
    }

    lastBracket = -1;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == ']') {
            lastBracket = i;
            break;
        }
    }

    if (firstBracket == -1 || lastBracket == -1 || firstBracket > lastBracket) {
        cout << -1 << endl;
        return 0;
    }

    firstColon = -1;
    for (int i = firstBracket + 1; i < lastBracket; i++) {
        if (s[i] == ':') {
            firstColon = i;
            break;
        }
    }

    lastColon = -1;
    for (int i = lastBracket - 1; i > firstBracket; i--) {
        if (s[i] == ':') {
            lastColon = i;
            break;
        }
    }

    if (firstColon == -1 || firstColon == lastColon) {
        cout << -1 << endl;
        return 0;
    }

    int cnt = 0;
    for (int i = firstColon + 1; i < lastColon; i++) {
        if (s[i] == '|')
            cnt += 1;
    }

    cout << 4 + cnt << endl;
}
