/*
* Build a trie. Everytime TypeLetter is called, add a child to the current node. The path from the root to the
  current node will be our current string.
* To handle GetLetter fast, we need to use binary jumping technique.
* To handle UndoCommands, we need another data structure to know where we are at the trie after executing the first k
  commands. This is simple, just use a vector.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXLG 20

struct Node {
  int depth;
  char ch;
  Node* ancestors[MAXLG + 3];

  Node(int depth_, char ch_, Node* parent = NULL) {
    depth = depth_;
    ch = ch_;
    for (int lg = 0; lg <= MAXLG; lg++) {
      ancestors[lg] = (parent == NULL ? NULL : parent->getKthParent((1 << lg) - 1));
    }
  }

  Node* getKthParent(int k) {
    Node* current = this;
    for (int lg = 0; lg <= MAXLG && current != NULL; lg++) {
      if (k & (1 << lg)) {
        current = current->ancestors[lg];
      }
    }

    return current;
  }
};

Node* root = new Node(0, '.');
Node* currentNode = root;

vector<Node*> positions;

void Init() {
  positions.push_back(root);
}

void TypeLetter(char L) {
  Node* newNode = new Node(currentNode->depth + 1, L, currentNode);

  positions.push_back(newNode);
  currentNode = newNode;
}

void UndoCommands(int U) {
  Node* node = positions[positions.size() - 1 - U];

  positions.push_back(node);
  currentNode = node;
}

char GetLetter(int P) {
  return currentNode->getKthParent(currentNode->depth - 1 - P)->ch;
}
