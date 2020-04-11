#include<bits/stdc++.h>
using namespace std;

int T, N;
vector<string> prefixes, suffixes, middles;

int findFirstAsterisk(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '*')
            return i;
    }
}

int findLastAsterisk(string s) {
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '*')
            return i;
    }
}

string getAnsPrefix() {
    string result = "";

    for (int i = 0; ; i++) {
        char current = '.';
        bool done = true;
        for (string prefix: prefixes) {
            if (i >= prefix.length()) continue;

            done = false;

            if (current == '.')
                current = prefix[i];
            else {
                if (prefix[i] != current)
                    return "*";
            }
        }

        if (done)
            break;
        else
            result = result + current;
    }

    return result;
}

string getAnsSuffix() {
    string result = "";

    for (int i = 0; ; i++) {
        char current = '.';
        bool done = true;

        for (string suffix: suffixes) {
            if (i >= suffix.length()) continue;

            done = false;

            if (current == '.')
                current = suffix[suffix.length() - i - 1];
            else {
                if (suffix[suffix.length() - i - 1] != current)
                    return "*";
            }
        }

        if (done)
            break;
        else
            result = current + result;
    }

    return result;
}

string getAnsMiddle() {
    string result = "";
    for (auto s: middles)
        result += s;

    return result;
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        prefixes.clear();
        suffixes.clear();
        middles.clear();
        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;

            int firstAsterisk = findFirstAsterisk(s);
            int lastAsterisk = findLastAsterisk(s);

            string prefix = s.substr(0, firstAsterisk);
            string suffix = s.substr(lastAsterisk + 1);
            string middle = "";

            for (int i = firstAsterisk + 1; i <= lastAsterisk - 1; i++) {
                if (s[i] != '*') {
                    middle += s[i];
                }
            }

            if (prefix.length() > 0)
                prefixes.push_back(prefix);

            if (suffix.length() > 0)
                suffixes.push_back(suffix);

            if (middle.length() > 0)
                middles.push_back(middle);
        }

        string ansPrefix = getAnsPrefix();
        string ansSuffix = getAnsSuffix();
        string ansMiddle = getAnsMiddle();

        string ans = (ansPrefix != "*" && ansSuffix != "*" ? ansPrefix + ansMiddle + ansSuffix : "*");

        cout << "Case #" << cases << ": " << ans << endl;
    }
}
