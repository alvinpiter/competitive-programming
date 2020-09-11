#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007

struct Node {
    bool isEnd;
    Node* children[26];

    Node(bool _isEnd) {
        isEnd = _isEnd;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};

string S;
int N, dp[5003];
Node* root = new Node(false);

void insert(string s) {
    Node* current = root;
    for (int i = 0; i < s.length(); i++) {
        int charIndex = s[i] - 'a';

        if (current->children[charIndex] == NULL) {
            Node* newNode = new Node(false);
            current->children[charIndex] = newNode;
        }

        current = current->children[charIndex];

        if (i == s.length() - 1)
            current->isEnd = true;
    }
}

int solve(int i) {
    if (i == S.length())
        return 1;

    if (dp[i] != -1)
        return dp[i];

    int total = 0;
    Node* current = root;

    for (int j = i; j < S.length(); j++) {
        int charIndex = S[j] - 'a';
        if (current->children[charIndex] == NULL)
            break;

        current = current->children[charIndex];

        if (current->isEnd)
            total = (total + solve(j + 1))%MOD;
    }

    return dp[i] = total;
}

int main() {
    cin >> S;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        string word;
        cin >> word;

        insert(word);
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(0) << endl;
}
