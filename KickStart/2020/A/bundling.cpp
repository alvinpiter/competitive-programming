#include<bits/stdc++.h>
using namespace std;

/*
length is the prefix length
count is how many prefix match this prefix
*/
struct Node {
    int length, count;
    Node* children[26];
    Node() {
        length = 0;
        count = 0;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};

int T, N, K;
Node* root;

void insert(string s) {
    Node* current = root;
    for (int i = 0; i < s.length(); i++) {
        int charIndex = s[i] - 'A';
        if (current->children[charIndex] == NULL) {
            current->children[charIndex] = new Node();
        }

        current = current->children[charIndex];
        current->length = i + 1;
        current->count += 1;
    }
}

int count(Node* current) {
    int result = current->count/K;
    for (int i = 0; i < 26; i++) {
        if (current->children[i] != NULL)
            result += count(current->children[i]);
    }

    return result;
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> K;

        root = new Node();
        for (int i = 1; i <= N; i++) {
            string s;
            cin >> s;

            insert(s);
        }

        cout << "Case #" << cases << ": " << count(root) << endl;
    }
}
