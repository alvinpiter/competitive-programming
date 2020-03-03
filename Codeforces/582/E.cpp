#include<bits/stdc++.h>
using namespace std;

int n;
string s, t, answer;
vector<char> chars;

bool check() {
    for (int i = 0; i < answer.length() - 1; i++) {
        if (answer.substr(i, 2) == s || answer.substr(i, 2) == t)
            return false;
    }
    return true;
}

int main() {
    cin >> n >> s >> t;

    chars.push_back('a');
    chars.push_back('b');
    chars.push_back('c');
    do {
        answer = "";
        for (int j = 0; j < 3 * n; j++)
            answer += chars[j/n];

        if (check())
            break;

        answer = "";
        for (int j = 0; j < 3 * n; j++)
            answer += chars[j%3];

        if (check())
            break;
    } while (next_permutation(chars.begin(), chars.end()));

    cout << "YES\n";
    cout << answer << endl;
}
