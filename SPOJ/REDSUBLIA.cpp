#include<bits/stdc++.h>
using namespace std;
#define MAXSTR "~~~~~~"

/*
best[i][str] -> Characters c such that (str.substr(0, i) + c + str.substr(i + 1)) exists in the dictionary
*/
map<string, vector<char> > best[6];

void add(string s) {
    for (int i = 0; i < 6; i++) {
        string leftOver = s.substr(0, i) + s.substr(i + 1);
        best[i][leftOver].push_back(s[i]);
    }
}

string query(string s) {
    string miniStr = MAXSTR;
    for (int i = 0; i < 6; i++) {
        string leftOver = s.substr(0, i) + s.substr(i + 1);

        if (best[i].find(leftOver) == best[i].end())
            continue;

        char miniChar = '~';
        for (int j = 0; j < best[i][leftOver].size(); j++) {
            char currentChar = best[i][leftOver][j];
            if (currentChar != s[i] && currentChar < miniChar)
                miniChar = currentChar;
        }

        if (miniChar != '~') {
            string temp = s.substr(0, i) + miniChar + s.substr(i + 1);
            miniStr = min(miniStr, temp);
        }
    }

    return miniStr;
}

int main() {
    int T, N;
    string type, W;

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        for (int i = 0; i < 6; i++)
            best[i].clear();

        cin >> N;

        cout << "Test " << cases << endl;
        for (int i = 0; i < N; i++) {
            cin >> type >> W;
            if (type == "W")
                add(W);
            else {
                string minStr = query(W);
                if (minStr == MAXSTR)
                    cout << "0\n";
                else
                    cout << minStr << endl;
            }
        }
    }
}
