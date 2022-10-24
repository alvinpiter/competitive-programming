/*
* Insert each word into a trie
* "Add" operation is the same as going an edge downward, while "Remove" operation is the same as
  going an edge upward. If there is a requirement that the printer must be empty after all operations
  are performed, then the answer is 2 * numberOfEdgesInTheTrie + numberOfWords.
* However, we are allowed to leave some letters in the printer, so it is best if we leave the longest word in
  the printer.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAX_NODE 500000

int numberOfNodesInTrie = 1; // Root is numbered 1
int trie[MAX_NODE + 3][26], maxDepth[MAX_NODE + 3];
bool isEndOfAWord[MAX_NODE + 3];

vector<char> result;

void insert(string s) {
  int currentNode = 1;
  for (int i = 0; i < s.length(); i++) {
    int charIndex = (s[i] - 'a');

    maxDepth[currentNode] = max(maxDepth[currentNode], (int) s.length() - i);
    if (trie[currentNode][charIndex] == -1) {
      trie[currentNode][charIndex] = ++numberOfNodesInTrie;
    }

    currentNode = trie[currentNode][charIndex];
  }

  isEndOfAWord[currentNode] = true;
}

void traverse(int currentNode) {
  if (isEndOfAWord[currentNode]) {
    result.push_back('P');
  }

  int deepestChildIdx = -1;
  for (int i = 0; i < 26; i++) {
    if (trie[currentNode][i] != -1 && (deepestChildIdx == -1 || maxDepth[trie[currentNode][i]] > maxDepth[trie[currentNode][deepestChildIdx]])) {
      deepestChildIdx = i;
    }
  }

  for (int i = 0; i < 26; i++) {
    if (trie[currentNode][i] != -1 && i != deepestChildIdx) {
      result.push_back((char) (i + 'a'));
      traverse(trie[currentNode][i]);
    }
  }

  if (deepestChildIdx != -1) {
    result.push_back((char) (deepestChildIdx + 'a'));
    traverse(trie[currentNode][deepestChildIdx]);
  }

  result.push_back('-');
}

int main() {
  int n;
  scanf("%d", &n);

  memset(trie, -1, sizeof(trie));
  memset(maxDepth, 0, sizeof(maxDepth));
  memset(isEndOfAWord, false, sizeof(isEndOfAWord));
  for (int i = 0; i < n; i++) {
    char s[25];
    scanf("%s", s);

    string w(s);

    insert(w);
  }

  traverse(1);

  while (result.back() == '-') {
    result.pop_back();
  }

  printf("%d\n", (int) result.size());
  for (auto r: result) {
    printf("%c\n", r);
  }
}
