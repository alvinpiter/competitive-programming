#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXK 20

int N, K, S1, S2, S3, S4, monsterMagic[MAXN + 3];
vector<int> libraryIndices;
int canKill[MAXK + 3]; //canKill[i] = set of monsters that can be killed by magic i

int numberOfMagicSets;
int magicSetToIdx[(1 << MAXK) + 3];
int idxToMagicSet[5000]; //C(20, 4)
vector<int> magicSetMagics[(1 << MAXK) + 3];

/*
dp[i][magicSetIndex]:
maximum number of monsters that can be killed if we start from library i and
with given magicSetIndex
*/
int dp[103][5000];

/*
counter[i][magic]:
how many monsters with magic between ith and (i + 1)th library.
*/
int counter[103][MAXK + 3];

/*
score[i][magicSetIndex]:
how many monsters between ith and (i + 1)th library that can be killed with
given magicSetIndex
*/
int score[103][5000];

vector<int> magicSetTransitionIndices[5000];

void initMagicSets() {
  memset(magicSetToIdx, -1, sizeof(magicSetToIdx));
  numberOfMagicSets = 0;

  for (int magicSet = 0; magicSet < (1 << MAXK); magicSet++) {
    for (int i = 0; i < MAXK; i++) {
      if (magicSet & (1 << i)) {
        magicSetMagics[magicSet].push_back(i);
      }
    }

    if (magicSetMagics[magicSet].size() == 4) {
      numberOfMagicSets++;
      magicSetToIdx[magicSet] = numberOfMagicSets;
      idxToMagicSet[numberOfMagicSets] = magicSet;
    }
  }
}

int getScore(int libIndex, int magicSetIndex) {
  if (score[libIndex][magicSetIndex] != -1) {
    return score[libIndex][magicSetIndex];
  }

  int magicSet = idxToMagicSet[magicSetIndex];

  int result = 0;

  int monsterSet = 0;
  for (int i = 0; i < magicSetMagics[magicSet].size(); i++) {
    monsterSet |= canKill[magicSetMagics[magicSet][i]];
  }

  for (int i = 0; i < MAXK; i++) {
    if (monsterSet & (1 << i)) {
      result += counter[libIndex][i];
    }
  }

  return score[libIndex][magicSetIndex] = result;
}

void initCounter() {
  memset(counter, 0, sizeof(counter));
  for (int libIndex = 0; libIndex < libraryIndices.size() - 1; libIndex++) {
    for (int i = libraryIndices[libIndex] + 1; i < libraryIndices[libIndex + 1]; i++) {
      counter[libIndex][monsterMagic[i]]++;
    }
  }
}

void initMagicSetTransitionIndices() {
  for (int idx = 1; idx <= numberOfMagicSets; idx++) {
    int magicSet = idxToMagicSet[idx];

    for (int i = 0; i < 4; i++) {
      for (int m = 0; m < K; m++) {
        int newMagicSet = magicSet ^ (1 << magicSetMagics[magicSet][i]) ^ (1 << m);
        if (magicSetToIdx[newMagicSet] != -1) {
          magicSetTransitionIndices[idx].push_back(magicSetToIdx[newMagicSet]);
        }
      }
    }
  }
}

int solve(int libIndex, int magicSetIndex) {
  if (libIndex == libraryIndices.size() - 1) {
    return 0;
  }

  if (dp[libIndex][magicSetIndex] != -1) {
    return dp[libIndex][magicSetIndex];
  }

  int magicSet = idxToMagicSet[magicSetIndex];

  int best = solve(libIndex + 1, magicSetIndex) + getScore(libIndex, magicSetIndex);

  //libIndex = 0 meaning we are at the first hypotethical library, so we can't learn anything yet.
  if (libIndex != 0) {
    //try learning a new magic
    for (int i = 0; i < magicSetTransitionIndices[magicSetIndex].size(); i++) {
      int newIndex = magicSetTransitionIndices[magicSetIndex][i];
      best = max(best, solve(libIndex + 1, newIndex) + getScore(libIndex, newIndex));
    }
  }

  return dp[libIndex][magicSetIndex] = best;
}

int main() {
  initMagicSets();

  scanf("%d%d", &N, &K);
  scanf("%d%d%d%d", &S1, &S2, &S3, &S4);

  for (int i = 0; i < K; i++) {
    canKill[i] = 0;
    for (int j = 0; j < K; j++) {
      char c;
      cin >> c;

      if (c == '1') {
        canKill[i] += (1 << j);
      }
    }
  }

  libraryIndices.push_back(0);
  for (int i = 1; i <= N; i++) {
    int roomType;

    scanf("%d", &roomType);
    if (roomType == 1) {
      scanf("%d", &monsterMagic[i]);
      monsterMagic[i]--;
    } else {
      libraryIndices.push_back(i);
    }
  }
  libraryIndices.push_back(N + 1);

  initCounter();
  initMagicSetTransitionIndices();

  memset(score, -1, sizeof(score));
  memset(dp, -1, sizeof(dp));

  int magicSet = (1 << (--S1)) + (1 << (--S2)) + (1 << (--S3)) + (1 << (--S4));
  int magicSetIndex = magicSetToIdx[magicSet];

  printf("%d\n", solve(0, magicSetIndex));
}
