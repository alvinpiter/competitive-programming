/*
color -> 0 means white, 1 means black

dpPrefix[j][k][color] -> Can the first j character obey the first k rules such that the j-th character is painted "color"
dpSuffix[j][k][color] -> Can the suffix starting from j-th character obey the rules starting from the k-th such that s[j] is painted "color"

For each index j, define:
canBlack[j] -> > 0 if there is a solution such that s[j] is painted black, 0 otherwise.
canWhite[j] -> > 0 if there is a solution such that s[j] is painted white, 0 otherwise.

canBlack[j] = dpPrefix[j][k][1] && dpSuffix[j + 1][k + 1][0]
canWhite[j] = dpPrefix[j][k][0] && (dpSuffix[j + 1][k + 1][0] || dpSuffix[j + 1][k + 1][1])
Try every possible k.

Complexity: O(NK)
*/

#include "paint.h"
#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXK 100

bool dpPrefix[MAXN + 3][MAXK + 3][2], dpSuffix[MAXN + 3][MAXK + 3][2];
int canBlack[MAXN + 3], canWhite[MAXN + 3];
int cntBlack[MAXN + 3], cntWhite[MAXN + 3];

std::string solve_puzzle(std::string s, std::vector<int> c) {
  int N = s.length();
  int K = c.size();

  cntBlack[0] = cntWhite[0] = 0;
  for (int i = 1; i <= N; i++) {
    cntBlack[i] = cntBlack[i - 1] + (s[i - 1] == 'X' ? 1 : 0);
    cntWhite[i] = cntWhite[i - 1] + (s[i - 1] == '_' ? 1 : 0);
  }

  dpPrefix[0][0][0] = true;
  dpPrefix[0][0][1] = false;
  for (int k = 1; k <= K; k++) {
    dpPrefix[0][k][0] = dpPrefix[0][k][1] = false;
  }
  for (int i = 1; i <= N; i++) {
    dpPrefix[i][0][0] = (cntBlack[i] == 0);
    dpPrefix[i][0][1] = false;
  }

  for (int i = 1; i <= N; i++) {
    for (int k = 1; k <= K; k++) {
      if (s[i - 1] == 'X') {
        dpPrefix[i][k][0] = false;
      } else {
        dpPrefix[i][k][0] = dpPrefix[i - 1][k][0] || dpPrefix[i - 1][k][1];
      }

      if (s[i - 1] == '_') {
        dpPrefix[i][k][1] = false;
      } else {
        dpPrefix[i][k][1] = (i >= c[k - 1] && (cntWhite[i] - cntWhite[i - c[k - 1]] == 0) && dpPrefix[i - c[k - 1]][k - 1][0]);
      }
    }
  }

  dpSuffix[N + 1][K + 1][0] = true;
  dpSuffix[N + 1][K + 1][1] = false;
  for (int k = 1; k <= K; k++) {
    dpSuffix[N + 1][k][0] = dpSuffix[N + 1][k][1] = false;
  }
  for (int i = 1; i <= N; i++) {
    dpSuffix[i][K + 1][0] = (cntBlack[N] - cntBlack[i - 1]) == 0;
    dpSuffix[i][K + 1][1] = false;
  }

  for (int i = N; i >= 1; i--) {
    for (int k = 1; k <= K; k++) {
      if (s[i - 1] == 'X') {
        dpSuffix[i][k][0] = false;
      } else {
        dpSuffix[i][k][0] = dpSuffix[i + 1][k][0] || dpSuffix[i + 1][k][1];
      }

      if (s[i - 1] == '_') {
        dpSuffix[i][k][1] = false;
      } else {
        dpSuffix[i][k][1] = (N - i + 1 >= c[k - 1] && (cntWhite[i + c[k - 1] - 1] - cntWhite[i - 1] == 0) && dpSuffix[i + c[k - 1]][k + 1][0]);
      }
    }
  }

  memset(canBlack, 0, sizeof(canBlack));
  memset(canWhite, 0, sizeof(canWhite));
  for (int i = 1; i <= N; i++) {
    bool canBeBlack = false, canBeWhite = false;
    for (int k = 0; k <= K; k++) {
      bool canBeBlack = (dpPrefix[i][k][1] && dpSuffix[i + 1][k + 1][0]);
      bool canBeWhite = (dpPrefix[i][k][0] && (dpSuffix[i + 1][k + 1][0] || dpSuffix[i + 1][k + 1][1]));

      if (canBeBlack) {
        canBlack[i - c[k - 1] + 1] += 1;
        canBlack[i + 1] -= 1;
      }

      if (canBeWhite) {
        canWhite[i] += 1;
        canWhite[i + 1] -= 1;
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    canBlack[i] += canBlack[i - 1];
    canWhite[i] += canWhite[i - 1];
  }

  string result = "";
  for (int i = 1; i <= N; i++) {
    if (canBlack[i] > 0 && canWhite[i] > 0) {
      result += '?';
    } else if (canBlack[i] > 0) {
      result += 'X';
    } else if (canWhite[i] > 0) {
      result += '_';
    }
  }

  return result;
}
