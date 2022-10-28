/*
1. Root the tree at node 0.
2. Run DFS to calculate the number of people living in each subtree.
3. Run another DFS to decide the best city for the arena. If we treat the current city as the
   arena, then the most congested road will be one of the edges incident to it.
*/

#include "traffic.h"
#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 1000000

vector<int> adj[MAXN + 3];
int P[MAXN + 3], bestCity;
LL sz[MAXN + 3], bestTraffic;

void dfs1(int u, int prev) {
   sz[u] = P[u];
   for (auto v: adj[u]) {
      if (v != prev) {
         dfs1(v, u);
         sz[u] += sz[v];
      }
   }
}

void dfs2(int u, int prev) {
   LL maxTraffic = sz[0] - sz[u]; // From u to its parent
   for (auto v: adj[u]) {
      if (v != prev) {
         maxTraffic = max(maxTraffic, sz[v]);
      }
   }

   if (maxTraffic < bestTraffic) {
      bestTraffic = maxTraffic;
      bestCity = u;
   }

   for (auto v: adj[u]) {
      if (v != prev) {
         dfs2(v, u);
      }
   }
}

int LocateCentre(int N, int p[], int S[], int D[]) {
   for (int i = 0; i < N; i++) P[i] = p[i];
   for (int i = 0; i < N - 1; i++) {
      adj[S[i]].push_back(D[i]);
      adj[D[i]].push_back(S[i]);
   }

   dfs1(0, -1);

   bestTraffic = 3LL * 1e18;
   bestCity = -1;

   dfs2(0, -1);

   return bestCity;
}
