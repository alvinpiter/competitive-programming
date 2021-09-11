#include<bits/stdc++.h>
using namespace std;
#define MAXN 25000
#define MAX_NODE 500000

int numberOfNodes = 1;
int trie[MAX_NODE][26], nodePriority[MAX_NODE];
bool isEndNode[MAX_NODE];
char charAtNode[MAX_NODE];

vector<char> answer;

int getCharIndex(char c) {
  return (int) (c - 'a');
}

void insert(string s, int priority) {
  int currentNode = 1;
  for (int i = 0; i < s.length(); i++) {
    int charIndex = getCharIndex(s[i]);

    if (trie[currentNode][charIndex] == -1) {
      trie[currentNode][charIndex] = ++numberOfNodes;
    }

    int nextNode = trie[currentNode][charIndex];

    charAtNode[nextNode] = s[i];
    nodePriority[nextNode] = priority;
    if (i == s.length() - 1) {
      isEndNode[nextNode] = true;
    }

    currentNode = nextNode;
  }
}

void DFS(int currentNode) {
  if (isEndNode[currentNode]) {
    answer.push_back('P');
  }

  for (int charIndex = 0; charIndex < 26; charIndex++) {
    int nextNode = trie[currentNode][charIndex];
    if (nextNode != -1 && nodePriority[nextNode] == 1) {
      answer.push_back(charAtNode[nextNode]);
      DFS(nextNode);
    }
  }

  for (int charIndex = 0; charIndex < 26; charIndex++) {
    int nextNode = trie[currentNode][charIndex];
    if (nextNode != -1 && nodePriority[nextNode] == 0) {
      answer.push_back(charAtNode[nextNode]);
      DFS(nextNode);
    }
  }

  answer.push_back('-');
}

int main() {
  int N, indexWithMaxLength = 1;
  string words[MAXN + 3];

  scanf("%d", &N);
  for (int i = 1; i <= N; i++) {
    char s[25];
    scanf("%s", s);

    string word(s);
    words[i] = word;

    if (words[i].length() > words[indexWithMaxLength].length()) {
      indexWithMaxLength = i;
    }
  }

  memset(trie, -1, sizeof(trie));
  memset(isEndNode, false, sizeof(isEndNode));
  for (int i = 1; i <= N; i++) {
    if (i != indexWithMaxLength) {
      insert(words[i], 1);
    }
  }

  insert(words[indexWithMaxLength], 0);

  DFS(1);

  //clean up answer vector first
  while (answer[answer.size() - 1] == '-') {
    answer.pop_back();
  }

  printf("%d\n", (int) answer.size());
  for (int i = 0; i < answer.size(); i++) {
    printf("%c\n", answer[i]);
  }
}
