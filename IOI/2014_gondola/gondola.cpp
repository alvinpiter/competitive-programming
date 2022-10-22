/*
Gondola Sequence Checking
-------------------------

* If there is a duplicated gondola, return 0.
* If all gondolas are > n, return 1.
* Otherwise, find the position of one of the original gondola, let this be idxOfOriginalGondola.
  Start from idxOfOriginalGondola, go around the circle and make sure all other original gondolas
  are in place.


Replacement Sequence
--------------------

* For each of the given gondola, find the original gondola that it replaces. Here's how:
  - If there is an original gondola, then just go around the circle starting from it.
  - If there is no original gondola, then we assume the original gondolas were ordered from 1 to n.
* Process the new gondolas starting from the smallest-numbered one. For example, there is a gondola numbered
  10 which replaces gondola 4. Then the replacement sequence will be:
  4 -> lastUsedGondola + 1 -> lastUsedGondola + 2 -> ... -> 9

  lastUsedGondola was initially set to n, and updated accordingly.


Count Replacement Sequences
---------------------------

Assume there are k new gondolas that appear in the sequence (sorted increasingly): g1, g2, ..., gk.
This means there are k original gondolas that are replaced.

(n + 1)-th gondola and (g1 - 1)-th gondola each can replace 1 of k positions.
g1-th gondola can replace exactly 1 position.
(g1 + 1)-th gondola and (g2 - 1)-th gondola each can replace 1 of (k - 1) positions.
g2-th gondola can replace exactly 1 position.
...
(g_k-1 + 1)-th gondola and (gk - 1)-th gondola each can replace 1 position.
gk-th gondola can replace exactly 1 position.

Apply multiplication rule here.

The special case is when there is no original gondola appear in the sequence. We need to multiply the
result by n, because there are n possible ordering of the original gondolas.
*/

#include "gondola.h"
#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000009

LL fastExponentiation(LL base, LL p) {
  if (p == 0)
    return 1;

  LL half = fastExponentiation(base, p/2);
  LL halfhalf = (half * half)%MOD;

  if (p % 2 == 0)
    return halfhalf;
  else
    return (halfhalf * base)%MOD;
}

int valid(int n, int gondolas[]) {
  set<int> uniqGondolas;
  int idxOfOriginalGondola = -1;

  for (int i = 0; i < n; i++) {
    uniqGondolas.insert(gondolas[i]);
    if (gondolas[i] <= n) {
      idxOfOriginalGondola = i;
    }
  }

  if (uniqGondolas.size() < n) {
    return 0;
  }

  if (idxOfOriginalGondola == -1) {
    return 1;
  }

  for (int i = idxOfOriginalGondola, step = 0; step < n; i = (i + 1)%n, step++) {
    if (gondolas[i] <= n && gondolas[i] != (gondolas[idxOfOriginalGondola] - 1 + step)%n + 1) {
      return 0;
    }
  }

  return 1;
}

int replacement(int n, int gondolas[], int replacementSeq[]) {
  int idxOfOriginalGondola = -1;
  for (int i = 0; i < n; i++) {
    if (gondolas[i] <= n) {
      idxOfOriginalGondola = i;
      break;
    }
  }

  vector<pair<int, int> > newGondolasWithOriginal;
  if (idxOfOriginalGondola == -1) {
    for (int i = 0; i < n; i++) {
      newGondolasWithOriginal.push_back({gondolas[i], i + 1});
    }
  } else {
    for (int i = idxOfOriginalGondola, step = 0; step < n; i = (i + 1)%n, step++) {
      if (gondolas[i] > n) {
        newGondolasWithOriginal.push_back({gondolas[i], (gondolas[idxOfOriginalGondola] - 1 + step)%n + 1});
      }
    }
  }

  sort(newGondolasWithOriginal.begin(), newGondolasWithOriginal.end());

  int cntReplacement = 0;
  int lastUsedGondola = n;
  for (auto [newGondola, originalGondola]: newGondolasWithOriginal) {
    replacementSeq[cntReplacement++] = originalGondola;
    for (int g = lastUsedGondola + 1; g < newGondola; g++) {
      replacementSeq[cntReplacement++] = g;
    }

    lastUsedGondola = newGondola;
  }

  return cntReplacement;
}

int countReplacement(int n, int gondolas[]) {
  if (!valid(n, gondolas)) {
    return 0;
  }

  vector<int> newGondolas;
  for (int i = 0; i < n; i++) {
    if (gondolas[i] > n) {
      newGondolas.push_back(gondolas[i]);
    }
  }

  int cntReplaced = newGondolas.size();

  sort(newGondolas.begin(), newGondolas.end());

  vector<int> gapSizes;
  for (int i = 0; i < newGondolas.size(); i++) {
    int prev = (i == 0 ? n : newGondolas[i - 1]);
    int gapSize = newGondolas[i] - prev - 1;
    gapSizes.push_back(gapSize);
  }

  LL result = 1;
  for (int i = 0; i < gapSizes.size(); i++) {
    LL numWays = fastExponentiation(cntReplaced - i, gapSizes[i]);
    result = (result * numWays)%MOD;
  }

  if (cntReplaced == n) {
    result = (result * n)%MOD;
  }

  return result;
}
