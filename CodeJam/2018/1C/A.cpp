#include<bits/stdc++.h>
using namespace std;

int T, N, L;
bool found = false;
set<char> charAtDepth[13];
string answer;
set<string> strings;

void traverse(int depth, string current) {
    if (found)
        return;

    if (depth == L) {
        if (strings.find(current) == strings.end()) {
            answer = current;
            found = true;
        }

        return;
    }

    for (auto c: charAtDepth[depth])
        traverse(depth + 1, current + c);
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> L;

        strings.clear();
        for (int j = 0; j < L; j++)
            charAtDepth[j].clear();

        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;

            strings.insert(s);

            for (int j = 0; j < L; j++) {
                charAtDepth[j].insert(s[j]);
            }
        }

        found = false;
        traverse(0, "");

        cout << "Case #" << cases << ": ";
        if (found)
            cout << answer << endl;
        else
            cout << "-\n";
    }
}
