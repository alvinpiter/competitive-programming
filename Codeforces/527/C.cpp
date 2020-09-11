#include<bits/stdc++.h>
using namespace std;
#define MAXN 100

int n;
char answer[2 * MAXN + 3];
string str[2 * MAXN + 3];
bool valid;

void validate(string pref, string suff) {
    string ori = pref + suff[suff.length() - 1];

    set<string> seenAsPrefix;
    for (int i = 1; i <= 2 * n - 2; i++) {
        if (ori.substr(0, str[i].length()) == str[i] && seenAsPrefix.find(str[i]) == seenAsPrefix.end()) {
            seenAsPrefix.insert(str[i]);
            answer[i] = 'P';
        } else if (ori.substr(n - str[i].length()) == str[i])
            answer[i] = 'S';
        else
            valid = false;
    }
}

int main() {
    cin >> n;

    string prefix = "", suffix;
    for (int i = 1; i <= 2 * n - 2; i++) {
        cin >> str[i];

        if (str[i].length() == n - 1) {
            if (prefix == "")
                prefix = str[i];
            else
                suffix = str[i];
        }
    }

    valid = true;

    validate(prefix, suffix);
    if (!valid)
        validate(suffix, prefix);

    for (int i = 1; i <= 2 * n - 2; i++)
        cout << answer[i];
    cout << endl;
}
