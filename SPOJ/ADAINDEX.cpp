#include<bits/stdc++.h>
using namespace std;

struct Node {
    int counter;
    Node* children[26];
    Node() {
        counter = 0;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};

void insert(Node* root, string str) {
    Node* current = root;
    for (int i = 0; i < str.length(); i++) {
        int charIndex = (str[i] - 'a');

        if (current->children[charIndex] == NULL) {
            Node* newNode = new Node;
            current->children[charIndex] = newNode;
        }

        current = current->children[charIndex];
        current->counter += 1;
    }
}

int query(Node* root, string str) {
    Node* current = root;
    for (int i = 0; i < str.length(); i++) {
        int charIndex = (str[i] - 'a');

        if (current->children[charIndex] == NULL)
            return 0;

        current = current->children[charIndex];

        if (i == str.length() - 1){
            return current->counter;
        }
    }
}

int main() {
    int N, Q;
    Node* root = new Node;

    cin >> N >> Q;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;

        insert(root, s);
    }

    for (int i = 0; i < Q; i++) {
        string s;
        cin >> s;

        cout << query(root, s) << endl;
    }
}
