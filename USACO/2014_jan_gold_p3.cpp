/*
* Assume each cells stand alone at first.
* Connect cells starting from the ones with lowest elevation difference first.
* Once there is a connected component of size at least T, then all of the cells belonging to the
  connected component has difficulty rating equals to the last difficulty difference.

Solution:
Disjoint-set data structure with small-to-large merging optimization.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXR 500
#define MAXN 250000

int R, C, T, h[MAXR + 3][MAXR + 3], parent[MAXN + 3];
int rating[MAXN + 3];
bool isRatingCalculated[MAXN + 3];
vector<pair<int, pair<int, int> > > edges;
vector<int> whoWithParent[MAXN + 3];

int id(int r, int c) {
  return (r - 1) * C + c;
}

int findParent(int u) {
  return (parent[u] == u ? u : parent[u] = findParent(parent[u]));
}

bool isSameSet(int u, int v) {
  return findParent(u) == findParent(v);
}

void join(int u, int v, int byWeight) {
  if (isSameSet(u, v)) {
    return;
  }

  int pu = findParent(u), pv = findParent(v);

  // Small-to-large merging
  int joinFrom = (whoWithParent[pu].size() > whoWithParent[pv].size() ? pv : pu);
  int joinTo = (joinFrom == pu ? pv : pu);

  int newSize = whoWithParent[pu].size() + whoWithParent[pv].size();
  if (newSize >= T) {
    // assign rating if hasn't

    int toProcess[] = {pu, pv};
    for (int i = 0; i < 2; i++) {
      int p = toProcess[i];
      if (!isRatingCalculated[p]) {
        for (int i = 0; i < whoWithParent[p].size(); i++) {
          int cell = whoWithParent[p][i];
          rating[cell] = byWeight;
          isRatingCalculated[cell] = true;
        }
      }
    }
  }

  for (int i = 0; i < whoWithParent[joinFrom].size(); i++) {
    whoWithParent[joinTo].push_back(whoWithParent[joinFrom][i]);
  }

  parent[joinFrom] = joinTo;
}

int main() {
  freopen("skilevel.in", "r", stdin);
  freopen("skilevel.out", "w", stdout);

  cin >> R >> C >> T;
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      cin >> h[i][j];
    }
  }

  for (int i = 1; i <= R; i++) {
    for (int j = 1; j < C; j++) {
      edges.push_back(make_pair(abs(h[i][j] - h[i][j + 1]), make_pair(id(i, j), id(i, j + 1))));
    }
  }

  for (int j = 1; j <= C; j++) {
    for (int i = 1; i < R; i++) {
      edges.push_back(make_pair(abs(h[i][j] - h[i + 1][j]), make_pair(id(i, j), id(i + 1, j))));
    }
  }

  sort(edges.begin(), edges.end());

  memset(isRatingCalculated, false, sizeof(isRatingCalculated));
  for (int i = 1; i <= R * C; i++) {
    parent[i] = i;
    whoWithParent[parent[i]].push_back(i);
  }

  for (int i = 0; i < edges.size(); i++) {
    pair<int, pair<int, int> > edge = edges[i];
    int weight = edge.first, u = edge.second.first, v = edge.second.second;

    join(u, v, weight);
  }

  LL ans = 0;

  if (T > 1) {
    for (int i = 1; i <= R; i++) {
      for (int j = 1; j <= C; j++) {
        int p;
        cin >> p;

        if (p == 1) {
          ans += rating[id(i, j)];
        }
      }
    }
  }

  cout << ans << endl;
}
